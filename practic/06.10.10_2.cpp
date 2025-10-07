#include <iostream>
using namespace std;
int main () {
    double pizzaPrice1 = 8.5, pizzaPrice2 = 10.0, pizzaPrice3 = 9.5, pizzaPrice4 = 11.0;
    int pizzaQty1 = 0, pizzaQty2 = 0, pizzaQty3 = 0, pizzaQty4 = 0;
    double drinkPrice1 = 2.5, drinkPrice2 = 3.0, drinkPrice3 = 1.5;
    int drinkQty1 = 0, drinkQty2 = 0, drinkQty3 = 0;
    int choice;
    int quantity;
    
    cout << "Добро пожаловать в пиццерию!" << endl;
    
    // цикл заказа
    do {
        cout << "\n\tМЕНЮ:" << endl;
        
        cout << "\nПиццы:" << endl;
        cout << "1. Маргарита - " << pizzaPrice1 << "$" << endl;
        cout << "2. Пепперони - " << pizzaPrice2 << "$" << endl;
        cout << "3. Гавайская - " << pizzaPrice3 << "$" << endl;
        cout << "4. Четыре сыра - " << pizzaPrice4 << "$" << endl;
        
        // Вывод меню напитков
        cout << "\nНапитки:" << endl;
        cout << "5. Кола - " << drinkPrice1 << "$" << endl;
        cout << "6. Сок - " << drinkPrice2 << "$" << endl;
        cout << "7. Вода - " << drinkPrice3 << "$" << endl;
        cout << "0. Завершить заказ" << endl;
        cout << "\nВведите код продукта: ";
        cin >> choice;
        
        if (choice == 0) {
            break;
        }
        
        cout << "Введите количество: ";
        cin >> quantity;
        
        switch(choice) {
            case 1:
                pizzaQty1 += quantity;
                cout << "Маргарита добавлена в заказ!" << endl;
                break;
            case 2:
                pizzaQty2 += quantity;
                cout << "Пепперони добавлена в заказ!" << endl;
                break;
            case 3:
                pizzaQty3 += quantity;
                cout << "Гавайская добавлена в заказ!" << endl;
                break;
            case 4:
                pizzaQty4 += quantity;
                cout << "Четыре сыра добавлена в заказ!" << endl;
                break;
            case 5:
                drinkQty1 += quantity;
                cout << "Кола добавлена в заказ!" << endl;
                break;
            case 6:
                drinkQty2 += quantity;
                cout << "Сок добавлен в заказ!" << endl;
                break;
            case 7:
                drinkQty3 += quantity;
                cout << "Вода добавлена в заказ!" << endl;
                break;
            default:
                cout << "Неверный код продукта!" << endl;
        }
        
    } while (true);
    
    // расчет суммы
    cout << "\nВаш чек:" << endl;
    double totalPizzaCost = 0;
    double totalDrinkCost = 0;
    int totalPizzaCount = 0;
    
    cout << "\nПиццы:" << endl;
    if (pizzaQty1 > 0) {
        double cost = pizzaQty1 * pizzaPrice1;
        totalPizzaCost += cost;
        totalPizzaCount += pizzaQty1;
        cout << "Маргарита - " << pizzaQty1 << " шт. - " << cost << "$" << endl;
    }
    if (pizzaQty2 > 0) {
        double cost = pizzaQty2 * pizzaPrice2;
        totalPizzaCost += cost;
        totalPizzaCount += pizzaQty2;
        cout << "Пепперони - " << pizzaQty2 << " шт. - " << cost << "$" << endl;
    }
    if (pizzaQty3 > 0) {
        double cost = pizzaQty3 * pizzaPrice3;
        totalPizzaCost += cost;
        totalPizzaCount += pizzaQty3;
        cout << "Гавайская - " << pizzaQty3 << " шт. - " << cost << "$" << endl;
    }
    if (pizzaQty4 > 0) {
        double cost = pizzaQty4 * pizzaPrice4;
        totalPizzaCost += cost;
        totalPizzaCount += pizzaQty4;
        cout << "Четыре сыра - " << pizzaQty4 << " шт. - " << cost << "$" << endl;
    }

    cout << "\nНапитки:" << endl;
    if (drinkQty1 > 0) {
        double cost = drinkQty1 * drinkPrice1;
        double drinkDiscount = 0;
        if (drinkPrice1 > 2.0 && drinkQty1 > 3) {
            drinkDiscount = cost * 0.15;
            cost -= drinkDiscount;
            cout << "Кола - " << drinkQty1 << " шт. - " << (drinkQty1 * drinkPrice1) << "$" << " (скидка 15%: - " << drinkDiscount << "$" << ")" << endl;
        } else {
            cout << "Кола - " << drinkQty1 << " шт. - " << cost << "$" << endl;
        }
        totalDrinkCost += cost;
    }
    if (drinkQty2 > 0) {
        double cost = drinkQty2 * drinkPrice2;
        double drinkDiscount = 0;
        if (drinkPrice2 > 2.0 && drinkQty2 > 3) {
            drinkDiscount = cost * 0.15;
            cost -= drinkDiscount;
            cout << "Сок - " << drinkQty2 << " шт. - " << (drinkQty2 * drinkPrice2) << "$" << " (скидка 15%: - " << drinkDiscount << "$" << ")" << endl;
        } else {
            cout << "Сок - " << drinkQty2 << " шт. - " << cost << "$" << endl;
        }
        totalDrinkCost += cost;
    }
    if (drinkQty3 > 0) {
        double cost = drinkQty3 * drinkPrice3;
        double drinkDiscount = 0;
        if (drinkPrice3 > 2.0 && drinkQty3 > 3) {
            drinkDiscount = cost * 0.15;
            cost -= drinkDiscount;
            cout << "Вода - " << drinkQty3 << " шт. - " << (drinkQty3 * drinkPrice3) << "$" << " (скидка 15%: - " << drinkDiscount << "$" << ")" << endl;
        } else {
            cout << "Вода - " << drinkQty3 << " шт. - " << cost << "$" << endl;
        }
        totalDrinkCost += cost;
    }
    
    double subtotal = totalPizzaCost + totalDrinkCost;
    
    cout << "\nПРОМЕЖУТОЧНЫЙ ИТОГ:" << endl;
    cout << "Пиццы: " << totalPizzaCost << "$" << endl;
    cout << "Напитки: " << totalDrinkCost << "$" << endl;
    cout << "Общая сумма: " << subtotal << "$" << endl;

    double totalDiscount = 0;
    
    int freePizzas = totalPizzaCount / 5;
    if (freePizzas > 0) {
        double averagePizzaPrice = 0;
        if (totalPizzaCount > 0) {
            averagePizzaPrice = totalPizzaCost / totalPizzaCount;
        }
        double pizzaDiscount = freePizzas * averagePizzaPrice;
        totalDiscount += pizzaDiscount;
        cout << "\nСКИДКИ:" << endl;
        cout << "Каждая 5-я пицца бесплатно: - " << pizzaDiscount << "$" << " (" << freePizzas << " пицц в подарок)" << endl;
    }
    
    double orderDiscount = 0;
    if (subtotal > 50.0) {
        orderDiscount = subtotal * 0.20;
        totalDiscount += orderDiscount;
        if (freePizzas > 0) {
            cout << "Скидка 20% на заказ > 50$: - " << orderDiscount << "$" << endl;
        } else {
            cout << "\nСкидки: " << endl;
            cout << "Скидка 20% на заказ > $50: -$" << orderDiscount << endl;
        }
    }
    
    double finalTotal = subtotal - totalDiscount;
    
    cout << "\nИтог к оплате:" << endl;
    cout << "Общая сумма: " << subtotal << "$" << endl;
    if (totalDiscount > 0) {
        cout << "Общая скидка: - " << totalDiscount << "$" << endl;
    }
    cout << "Итого к оплате: " << finalTotal << "$" << endl;
    
    return 0;
}