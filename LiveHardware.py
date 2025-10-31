import os
import platform
import time
import pygame
import GPUtil
import psutil
import subprocess
import json
import csv
from pygame import mixer
from collections import deque
from datetime import datetime

from pygame.examples.midi import BACKGROUNDCOLOR

# Инициализация pygame
pygame.init()
mixer.init()
window_size = (1000, 650)
pygame.display.set_caption("LiveHardware")
screen = pygame.display.set_mode(window_size)
clock = pygame.time.Clock()

# Глобальные переменные для логирования
LOGGING_ENABLED = False
LOG_FILE = "resource_log.csv"

# Цвета для тем
THEMES = {
    'light': {
        'background': (240, 240, 240),
        'text': (0, 0, 0),
        'button': (70, 70, 70),
        'button_hover': (100, 100, 100),
        'graph_bg': (200, 200, 200)
    },
    'dark': {
        'background': (40, 40, 40),
        'text': (255, 255, 255),
        'button': (100, 100, 100),
        'button_hover': (130, 130, 130),
        'graph_bg': (80, 80, 80)
    }
}

def init_theme(dark_mode=False):
    theme = 'dark' if dark_mode else 'light'
    globals().update({
        'BACKGROUND': THEMES[theme]['background'],
        'BLACK': THEMES[theme]['text'],
        'BUTTON_COLOR': THEMES[theme]['button'],
        'BUTTON_HOVER': THEMES[theme]['button_hover'],
        'GRAY': THEMES[theme]['graph_bg']
    })


# Цвета
# BACKGROUND = LIGHT_THEME['BACKGROUND']
# BLACK = LIGHT_THEME['TEXT']
WHITE = (255, 255, 255)
RED = (255, 50, 50)
GREEN = (50, 200, 50)
BLUE = (50, 50, 255)
# GRAY = LIGHT_THEME['GRAPH_BG']
# BUTTON_COLOR = LIGHT_THEME['BUTTON']
# BUTTON_HOVER = LIGHT_THEME['BUTTON_HOVER']

# Настройки шрифтов
font = pygame.font.SysFont('Aptos', 32)
small_font = pygame.font.SysFont('Aptos', 28)
font_button = pygame.font.SysFont('Aptos', 26)

# Настройки графиков
GRAPH_WIDTH = 600
GRAPH_HEIGHT = 200
GRAPH_X = 350
GRAPH_Y = 380
GRAPH_X_NET = 250
GRAPH_Y_NET = 380
HISTORY_LENGTH = 60

# История данных
cpu_history = deque([0] * HISTORY_LENGTH, maxlen=HISTORY_LENGTH)
gpu_history = deque([0] * HISTORY_LENGTH, maxlen=HISTORY_LENGTH)
ram_history = deque([0] * HISTORY_LENGTH, maxlen=HISTORY_LENGTH)
net_sent_history = deque([0] * HISTORY_LENGTH, maxlen=HISTORY_LENGTH)
net_recv_history = deque([0] * HISTORY_LENGTH, maxlen=HISTORY_LENGTH)

# Состояния вкладок
TAB_SYSTEM = 0
TAB_GPU = 1
TAB_RAM = 2
TAB_NET = 3
TAB_SET = 4
current_tab = TAB_SYSTEM

sound = pygame.mixer.Sound('click.ogg')


class Button:
    def __init__(self, x, y, width, height, text):
        self.rect = pygame.Rect(x, y, width, height)
        self.text = text
        self.is_hovered = False

    def draw(self, surface):
        color = BUTTON_HOVER if self.is_hovered else BUTTON_COLOR
        pygame.draw.rect(surface, color, self.rect, border_radius=5)
        pygame.draw.rect(surface, BLACK, self.rect, 2, border_radius=5)

        text_surf = font_button.render(self.text, True, WHITE)
        text_rect = text_surf.get_rect(center=self.rect.center)
        surface.blit(text_surf, text_rect)

    def check_hover(self, pos):
        self.is_hovered = self.rect.collidepoint(pos)
        return self.is_hovered

    def is_clicked(self, pos, event):
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            return self.rect.collidepoint(pos)
        return False



# Создание кнопок
buttons = [
    Button(10, 80, 230, 40, "Системная информация"),
    Button(10, 130, 230, 40, "Информация о GPU"),
    Button(10, 180, 230, 40, "Информация о ОЗУ"),
    Button(10, 230, 230, 40, "Информация о интернете"),
    Button(10, 300, 230, 40, "Управление"),

    Button(260, 150, 200, 40, "Выключение ПК"),
    Button(260, 200, 200, 40, "Перезагрузка ПК"),
    Button(260, 250, 200, 40, "Сменить тему"),
    Button(470, 150, 200, 40, "Логирование(On/Off)"),
    Button(470, 200, 200, 40, "Последний лог"),
    Button(470, 250, 200, 40, "Кнопка 6")
]

def init_theme(dark_mode=False):
    theme = 'dark' if dark_mode else 'light'
    globals().update({
        'BACKGROUND': THEMES[theme]['background'],
        'BLACK': THEMES[theme]['text'],
        'BUTTON_COLOR': THEMES[theme]['button'],
        'BUTTON_HOVER': THEMES[theme]['button_hover'],
        'GRAY': THEMES[theme]['graph_bg']
    })

# Функция переключения темы
def toggle_theme():
    global DARK_THEME
    DARK_THEME = not DARK_THEME
    init_theme(DARK_THEME)
    save_theme()

    fade_screen()
    init_theme(DARK_THEME)
    fade_screen()

# Функции сохранения/загрузки темы
def save_theme():
    try:
        with open('theme_config.json', 'w') as f:
            json.dump({'dark_theme': DARK_THEME}, f)
    except Exception as e:
        print(f"Ошибка сохранения темы: {e}")

def load_theme():
    try:
        with open('theme_config.json', 'r') as f:
            return json.load(f).get('dark_theme', False)
    except:
        return False

def fade_screen():
    fade_surface = pygame.Surface(window_size)
    fade_surface.fill(BACKGROUND)
    for alpha in range(0, 255, 15):
        fade_surface.set_alpha(alpha)
        screen.blit(fade_surface, (0, 0))
        pygame.display.flip()
        pygame.time.delay(30)

DARK_THEME = load_theme()
init_theme()


def unit(bytes, suffix="B"):
    #Конверт. (KB, MB, GB и т.д.)
    factor = 1024
    for unit in ["", "K", "M", "G", "T", "P"]:
        if bytes < factor:
            return f"{bytes:.2f}{unit}{suffix}"
        bytes /= factor


def get_system_info():
    #Собирает информацию о системе
    info = {}
    try:
        gpus = GPUtil.getGPUs()
        uname = platform.uname()
        cpufreq = psutil.cpu_freq()
        mem = psutil.virtual_memory()
        internet = psutil.net_io_counters()

        # Информация о системе
        info['system'] = uname.system
        info['cores'] = psutil.cpu_count(logical=True)
        cpu_usage = psutil.cpu_percent()
        info['cpu_usage'] = cpu_usage
        cpu_history.append(cpu_usage)
        info['cpu_freq_max'] = cpufreq.max if cpufreq else "N/A"

        # Информация о памяти
        mem_total = (int(mem.total)) / (1024 * 1024 * 1024)
        info['mem_total'] = round(mem_total)
        info['mem_used'] = unit(mem.used)
        ram_percent = mem.percent
        info['mem_percent'] = ram_percent
        ram_history.append(ram_percent)

        # Информация о GPU
        if gpus:
            gpu = gpus[0]
            info['gpu_name'] = gpu.name
            info['gpu_mem'] = f"{gpu.memoryTotal}MB"
            info['gpu_temp'] = f"{gpu.temperature}°C"
            gpu_load = gpu.load * 100
            info['gpu_load'] = f"{gpu_load:.1f}%"
            gpu_history.append(gpu_load)
        else:
            info['gpu_name'] = "N/A"
            info['gpu_mem'] = "N/A"
            info['gpu_temp'] = "N/A"
            info['gpu_load'] = "N/A"
            gpu_history.append(0)

        # Информация о сети
        net_sent = internet.bytes_sent
        net_recv = internet.bytes_recv
        info['net_sent'] = unit(net_sent)
        info['net_recv'] = unit(net_recv)
        net_sent_history.append(net_sent / (1024 * 1024))  # Конверт в MB
        net_recv_history.append(net_recv / (1024 * 1024))  # Конверт в MB

    except Exception as e:
        print(f"Ошибка при получении информации о системе: {e}")

    return info


def draw_graph(surface, history, position, size, color=RED, title="", y_label="%", max_value=100):
    # График на основе исторических данных
    x, y = position
    width, height = size

    # Фон
    pygame.draw.rect(surface, GRAY, (x, y, width, height))
    pygame.draw.rect(surface, BLACK, (x, y, width, height), 1)

    # Сетку и подписи
    for i in range(0, 101, 20):
        y_pos = y + height - (i * height / 100)
        pygame.draw.line(surface, (220, 220, 220), (x, y_pos), (x + width, y_pos))
        percent_text = small_font.render(f"{int(max_value * i / 100)}{y_label}", True, BLACK)
        surface.blit(percent_text, (x - 50, y_pos - 10))

    # Линию графика
    if len(history) > 1:
        points = []
        for i, value in enumerate(history):
            x_pos = x + (i * width / (len(history) - 1))
            y_pos = y + height - (value * height / max_value)
            points.append((x_pos, y_pos))

            if len(points) > 1:
                pygame.draw.lines(surface, color, False, points, 2)

            # Заголовок
            title_text = small_font.render(title, True, BLACK)
            surface.blit(title_text, (x, y - 20))


def draw_system_info(surface, info):
    # Отображает информацию о системе
    y_offset = 80

    # Информация о системе
    sys_title = font.render("Системная информация", True, BLACK)
    surface.blit(sys_title, (250, y_offset))
    y_offset += 40

    texts = [
        f"Система: {info['system']}",
        f"Ядра: {info['cores']}",
        f"Использование CPU: {info['cpu_usage']}%",
        f"Максимальная частота CPU: {info['cpu_freq_max']}MHz"
    ]

    for text in texts:
        rendered = small_font.render(text, True, BLACK)
        surface.blit(rendered, (260, y_offset))
        y_offset += 30

    # График загрузки CPU
    draw_graph(surface, cpu_history, (GRAPH_X, GRAPH_Y), (GRAPH_WIDTH, GRAPH_HEIGHT),
               BLUE, "Использование CPU", "%", 100)


def draw_gpu_info(surface, info):
    # Отображает информацию о GPU
    y_offset = 80

    # Информация о GPU
    gpu_title = font.render("Информация о GPU", True, BLACK)
    surface.blit(gpu_title, (250, y_offset))
    y_offset += 40

    texts = [
        f"GPU: {info['gpu_name']}",
        f"Память GPU: {info['gpu_mem']}",
        f"Температура GPU: {info['gpu_temp']}",
        f"Загрузка GPU: {info['gpu_load']}"
    ]

    for text in texts:
        rendered = small_font.render(text, True, BLACK)
        surface.blit(rendered, (260, y_offset))
        y_offset += 30

    # График загрузки GPU
    draw_graph(surface, gpu_history, (GRAPH_X, GRAPH_Y), (GRAPH_WIDTH, GRAPH_HEIGHT),
               GREEN, "Загрузка GPU", "%", 100)


def draw_ram_info(surface, info):
    # Отображает информацию об ОЗУ
    y_offset = 80

    # Информация о памяти
    ram_title = font.render("Информация о ОЗУ", True, BLACK)
    surface.blit(ram_title, (250, y_offset))
    y_offset += 40

    texts = [
        f"Объем RAM: {info['mem_total']}GB",
        f"Используемая RAM: {info['mem_used']}",
        f"Использование RAM: {info['mem_percent']}%"
    ]

    for text in texts:
        rendered = small_font.render(text, True, BLACK)
        surface.blit(rendered, (260, y_offset))
        y_offset += 30

    # График использования памяти
    draw_graph(surface, ram_history, (GRAPH_X, GRAPH_Y), (GRAPH_WIDTH, GRAPH_HEIGHT),
               RED, "Использование RAM", "%", 100)


def draw_net_info(surface, info):
    # Отображает информацию о сети
    y_offset = 80

    # Информация о сети
    net_title = font.render("Информация о Сети", True, BLACK)
    surface.blit(net_title, (250, y_offset))
    y_offset += 40

    texts = [
        f"Отправленные данные: {info['net_sent']}",
        f"Полученные данные: {info['net_recv']}"
    ]

    for text in texts:
        rendered = small_font.render(text, True, BLACK)
        surface.blit(rendered, (260, y_offset))
        y_offset += 30

    # Максимальное значение для масштабирования
    max_net = max(max(net_sent_history), max(net_recv_history)) if (net_sent_history and net_recv_history) else 10
    max_net = max(max_net, 10)  # Минимальный масштаб 10MB

    # Графики сети
    draw_graph(surface, net_sent_history, (GRAPH_X_NET, GRAPH_Y_NET), (GRAPH_WIDTH // 2 - 10, GRAPH_HEIGHT),
               BLUE, "Отправленные данные (MB)", "MB", 20000)
    draw_graph(surface, net_recv_history, (GRAPH_X + GRAPH_WIDTH // 2 + 10, GRAPH_Y),
               (GRAPH_WIDTH // 2 - 10, GRAPH_HEIGHT),
               GREEN, "Полученные данные (MB)", "MB", 20000)

def draw_set(surface, info):
    # Отображает панель управления
    y_offset = 80

    # Заголовок
    set_title = font.render("Управление", True, BLACK)
    surface.blit(set_title, (250, y_offset))
    y_offset += 40

    # Отображаем только кнопки управления (индексы 5-10)
    mouse_pos = pygame.mouse.get_pos()
    for button in buttons[5:11]:
        button.check_hover(mouse_pos)
        button.draw(surface)

    info_text = small_font.render("Используйте кнопки для управления системой", True, BLACK)
    surface.blit(info_text, (260, y_offset))

    theme_indicator = "Темная тема" if DARK_THEME else "Светлая тема"
    theme_text = small_font.render(f"Текущая тема: {theme_indicator}", True, BLACK)
    surface.blit(theme_text, (260, 300))

    log_status = "ВКЛ" if LOGGING_ENABLED else "ВЫКЛ"
    status_text = small_font.render(f"Логирование: {log_status}", True, BLACK)
    surface.blit(status_text, (550, 300))

    if LOGGING_ENABLED:
        file_text = small_font.render(f"Файл: {LOG_FILE}", True, BLACK)
        surface.blit(file_text, (500, 340))


def render_info(surface, info):
    # Отрисовывает весь интерфейс
    surface.fill(BACKGROUND)

    # Заголовок
    title = font.render("Live Hardware Monitor", True, BLACK)
    surface.blit(title, (20, 20))

    # Основные кнопки навигации (всегда видны)
    mouse_pos = pygame.mouse.get_pos()
    for button in buttons[:5]:  # Только первые 5 кнопок (навигация)
        button.check_hover(mouse_pos)
        button.draw(surface)

    # Содержимое текущей вкладки
    if current_tab == TAB_SYSTEM:
        draw_system_info(surface, info)
    elif current_tab == TAB_GPU:
        draw_gpu_info(surface, info)
    elif current_tab == TAB_RAM:
        draw_ram_info(surface, info)
    elif current_tab == TAB_NET:
        draw_net_info(surface, info)
    elif current_tab == TAB_SET:
        mouse_pos = pygame.mouse.get_pos()
        for button in buttons[5:]:  # Кнопки управления (индексы 5+)
            button.check_hover(mouse_pos)
            button.draw(surface)
        draw_set(surface, info)


def show_confirmation_dialog(surface, message):
    #Показывает диалоговое окно подтверждения
    dialog_width, dialog_height = 400, 150
    dialog_x = (window_size[0] - dialog_width) // 2
    dialog_y = (window_size[1] - dialog_height) // 2

    # Фон диалога
    pygame.draw.rect(surface, BACKGROUND, (dialog_x, dialog_y, dialog_width, dialog_height))
    pygame.draw.rect(surface, BLACK, (dialog_x, dialog_y, dialog_width, dialog_height), 2)

    # Текст сообщения
    lines = message.split('\n')
    for i, line in enumerate(lines):
        text_surf = small_font.render(line, True, BLACK)
        text_rect = text_surf.get_rect(center=(window_size[0] // 2, dialog_y + 40 + i * 30))
        surface.blit(text_surf, text_rect)

    # Кнопки подтверждения
    yes_btn = Button(dialog_x + 50, dialog_y + 100, 120, 35, "Да")
    no_btn = Button(dialog_x + 230, dialog_y + 100, 120, 35, "Нет")

    mouse_pos = pygame.mouse.get_pos()
    yes_btn.check_hover(mouse_pos)
    no_btn.check_hover(mouse_pos)

    yes_btn.draw(surface)
    no_btn.draw(surface)

    pygame.display.flip()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                if yes_btn.rect.collidepoint(event.pos):
                    sound.play()
                    return True
                elif no_btn.rect.collidepoint(event.pos):
                    sound.play()
                    return False
        clock.tick(60)


def show_message(surface, message, duration=2000):

    #Отображает временное сообщение
    msg_surface = pygame.Surface((600, 50))
    msg_surface.fill(BACKGROUND)
    pygame.draw.rect(msg_surface, BLACK, (0, 0, 600, 50), 2)

    lines = message.split('\n')
    for i, line in enumerate(lines):
        text = small_font.render(line, True, BLACK)
        msg_surface.blit(text, (10, 5 + i * 20))

    x = (window_size[0] - 600) // 2
    y = (window_size[1] - 50) // 2

    surface.blit(msg_surface, (x, y))
    pygame.display.flip()

    if duration > 0:
        pygame.time.delay(duration)

def toggle_logging():
    global LOGGING_ENABLED
    LOGGING_ENABLED = not LOGGING_ENABLED

    # Создаем заголовки при первом запуске
    if LOGGING_ENABLED and not os.path.exists(LOG_FILE):
        with open(LOG_FILE, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['Timestamp', 'CPU%', 'RAM%', 'GPU%', 'NetSent(MB)', 'NetRecv(MB)'])

    return LOGGING_ENABLED

def view_logs():
    try:
        if not os.path.exists(LOG_FILE):
            return "Файл лога не найден"

        with open(LOG_FILE, 'r') as f:
            lines = f.readlines()
            return "Последние записи:\n" + "".join(lines[-5:]) if lines else "Лог пуст"
    except Exception as e:
        return f"Ошибка чтения лога: {str(e)}"


def main():

    global current_tab

    running = True
    last_update = 0
    update_interval = 1.0

    while running:
        current_time = time.time()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            # Обработка кликов по кнопкам
            mouse_pos = pygame.mouse.get_pos()
            for i, button in enumerate(buttons):
                if button.is_clicked(mouse_pos, event):
                    if event.button == 1:
                        sound.play()
                        if i == 0:
                            current_tab = TAB_SYSTEM
                        elif i == 1:
                            current_tab = TAB_GPU
                        elif i == 2:
                            current_tab = TAB_RAM
                        elif i == 3:
                            current_tab = TAB_NET
                        elif i == 4:
                            current_tab = TAB_SET
                        elif 5 <= i <= 10:  # Обработка новых кнопок управления
                            if i == 5:  # Кнопка "Выключение ПК"
                                if show_confirmation_dialog(screen, "Вы уверены, что хотите\nвыключить компьютер?"):
                                    try:
                                        # Для Windows
                                        if platform.system() == "Windows":
                                            subprocess.run(["shutdown", "/s", "/t", "10"])
                                        # Для Linux/Mac
                                        else:
                                            subprocess.run(["shutdown", "-h", "now"])
                                    except Exception as e:
                                        print(f"Ошибка при выключении: {e}")
                            elif i == 6:  # Кнопка "Перезагрузки ПК"
                                if show_confirmation_dialog(screen, "Вы уверены, что хотите\nперезагрузить компьютер?"):
                                    try:
                                        # Для Windows
                                        if platform.system() == "Windows":
                                            subprocess.run(["shutdown", "/r ", "/t", "10"])
                                        # Для Linux/Mac
                                        else:
                                            subprocess.run(["shutdown", "-r", "now"])
                                    except Exception as e:
                                        print(f"Ошибка при перезагрузке: {e}")

                            elif i == 7: # Кнопка Сменить Тему
                                sound.play()
                                toggle_theme()

                            elif i == 8:
                                sound.play()
                                if toggle_logging():
                                    show_message(screen, "Логирование начато\nФайл: " + LOG_FILE)
                                else:
                                    show_message(screen, "Логирование остановлено")

                            elif i == 9:
                                sound.play()
                                log_content = view_logs()
                                show_message(screen, log_content, duration=5000)
                            else:
                                print(f"Нажата кнопка {i - 4}")

        if current_time - last_update > update_interval:
            info = get_system_info()
            last_update = current_time

        if LOGGING_ENABLED:
            with open(LOG_FILE, 'a', newline='') as f:
                writer = csv.writer(f)
                writer.writerow([
                    datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                    info.get('cpu_usage', 0),
                    info.get('mem_percent', 0),
                    float(info.get('gpu_load', '0').replace('%', '')) if isinstance(info.get('gpu_load'), str) else 0,
                    net_sent_history[-1] if net_sent_history else 0,
                    net_recv_history[-1] if net_recv_history else 0
                ])

        render_info(screen, info)
        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()
