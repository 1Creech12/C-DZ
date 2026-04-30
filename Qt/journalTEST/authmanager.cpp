#include "AuthManager.h"
#include "ApiClient.h"  // Включаем здесь, а не в .h
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDateTime>

AuthManager::AuthManager(ApiClient *apiClient, QObject *parent)
    : QObject(parent)
    , m_apiClient(apiClient)
    , m_settings("TopAcademy", "JournalApp")
{
    connect(&m_refreshTimer, &QTimer::timeout, this, &AuthManager::onRefreshTimeout);
    loadFromSettings();
}

void AuthManager::login(const QString &username, const QString &password)
{
    QJsonObject body;
    body["application_key"] = QString("6a56a5df2667e65aab73ce76d1dd737f7d1faef9c52e8b8c55ac75f565d8e8a6");
    body["id_city"] = QJsonValue::Null;
    body["username"] = username;
    body["password"] = password;

    m_apiClient->post("/auth/login", body,
                      [this](QJsonObject response) {
                          processLoginResponse(response);
                      },
                      [this](QString error) {
                          qDebug() << "❌ Ошибка входа:" << error;
                          emit loginFailed("Ошибка входа: " + error);
                      }
                      );
}

void AuthManager::tryAutoLogin()
{
    if (m_authData.isValid()) {
        if (!m_authData.isExpired()) {
            m_apiClient->setAuthToken(m_authData.access_token);
            scheduleAutoRefresh();
            emit loginSuccess(m_authData);
            qDebug() << "✅ Автовход успешен";
        } else if (!m_authData.refresh_token.isEmpty()) {
            refreshToken();
        }
    }
}

void AuthManager::logout()
{
    m_authData = AuthData();
    m_apiClient->clearAuthToken();
    m_refreshTimer.stop();
    clearSettings();
    emit loggedOut();
}

void AuthManager::refreshToken()
{
    QJsonObject body;
    body["refresh_token"] = m_authData.refresh_token;
    body["application_key"] = QString("6a56a5df2667e65aab73ce76d1dd737f7d1faef9c52e8b8c55ac75f565d8e8a6");

    m_apiClient->post("/auth/refresh", body,
                      [this](QJsonObject response) {
                          processRefreshResponse(response);
                      },
                      [this](QString error) {
                          qDebug() << "❌ Не удалось обновить токен:" << error;
                          emit loginFailed("Сессия истекла, войдите заново");
                          logout();
                      }
                      );
}

void AuthManager::processLoginResponse(const QJsonObject &json)
{
    m_authData.access_token = json["access_token"].toString();
    m_authData.refresh_token = json["refresh_token"].toString();
    m_authData.expires_in_access = json["expires_in_access"].toVariant().toLongLong();
    m_authData.expires_in_refresh = json["expires_in_refresh"].toVariant().toLongLong();
    m_authData.user_type = json["user_type"].toInt();
    m_authData.user_role = json["user_role"].toString();

    QJsonObject city = json["city_data"].toObject();
    m_authData.city_data.id_city = city["id_city"].toInt();
    m_authData.city_data.name = city["name"].toString();
    m_authData.city_data.prefix = city["prefix"].toString();
    m_authData.city_data.timezone_name = city["timezone_name"].toString();
    m_authData.city_data.country_code = city["country_code"].toString();
    m_authData.city_data.translate_key = city["translate_key"].toString();
    m_authData.city_data.market_status = city["market_status"].toInt();

    QJsonObject jwtPayload = decodeJwtPayload(m_authData.access_token);
    m_authData.user_id = jwtPayload["userId"].toInt();

    m_apiClient->setAuthToken(m_authData.access_token);
    saveToSettings();
    scheduleAutoRefresh();

    qDebug() << "✅ Вход выполнен. Пользователь ID:" << m_authData.user_id;
    qDebug() << "   Роль:" << m_authData.user_role;
    qDebug() << "   Город:" << m_authData.city_data.name;

    emit loginSuccess(m_authData);
}

void AuthManager::processRefreshResponse(const QJsonObject &json)
{
    m_authData.access_token = json["access_token"].toString();
    m_authData.expires_in_access = json["expires_in_access"].toVariant().toLongLong();
    m_apiClient->setAuthToken(m_authData.access_token);
    saveToSettings();
    scheduleAutoRefresh();
    qDebug() << "🔄 Токен обновлён";
    emit tokenRefreshed();
}

void AuthManager::saveToSettings()
{
    m_settings.setValue("auth/access_token", m_authData.access_token);
    m_settings.setValue("auth/refresh_token", m_authData.refresh_token);
    m_settings.setValue("auth/expires_in_access", m_authData.expires_in_access);
    m_settings.setValue("auth/expires_in_refresh", m_authData.expires_in_refresh);
    m_settings.setValue("auth/user_type", m_authData.user_type);
    m_settings.setValue("auth/user_role", m_authData.user_role);
    m_settings.setValue("auth/user_id", m_authData.user_id);
    m_settings.setValue("auth/city_name", m_authData.city_data.name);
    m_settings.setValue("auth/city_id", m_authData.city_data.id_city);
    m_settings.sync();
}

void AuthManager::loadFromSettings()
{
    m_authData.access_token = m_settings.value("auth/access_token").toString();
    m_authData.refresh_token = m_settings.value("auth/refresh_token").toString();
    m_authData.expires_in_access = m_settings.value("auth/expires_in_access").toLongLong();
    m_authData.expires_in_refresh = m_settings.value("auth/expires_in_refresh").toLongLong();
    m_authData.user_type = m_settings.value("auth/user_type").toInt();
    m_authData.user_role = m_settings.value("auth/user_role").toString();
    m_authData.user_id = m_settings.value("auth/user_id").toInt();
    m_authData.city_data.name = m_settings.value("auth/city_name").toString();
    m_authData.city_data.id_city = m_settings.value("auth/city_id").toInt();
}

void AuthManager::clearSettings()
{
    m_settings.remove("auth");
    m_settings.sync();
}

void AuthManager::scheduleAutoRefresh()
{
    qint64 now = QDateTime::currentSecsSinceEpoch();
    qint64 refreshIn = m_authData.expires_in_access - now - 300;

    if (refreshIn > 0) {
        m_refreshTimer.start(refreshIn * 1000);
        qDebug() << "⏰ Обновление токена через" << refreshIn / 60 << "минут";
    } else {
        refreshToken();
    }
}

void AuthManager::onRefreshTimeout()
{
    refreshToken();
}

QJsonObject AuthManager::decodeJwtPayload(const QString &token) const
{
    QStringList parts = token.split('.');
    if (parts.size() != 3) return QJsonObject();

    QByteArray payload = QByteArray::fromBase64(parts[1].toUtf8(), QByteArray::Base64UrlEncoding);
    QJsonDocument doc = QJsonDocument::fromJson(payload);
    return doc.object();
}

bool AuthManager::isAuthenticated() const
{
    return m_authData.isValid() && !m_authData.isExpired();
}

QString AuthManager::accessToken() const
{
    return m_authData.access_token;
}

const AuthData& AuthManager::authData() const
{
    return m_authData;
}