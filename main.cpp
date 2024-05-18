#include <list>
#include <iostream>
#include <string>

using namespace std;

class ChangeCalculator {
private:
    list<pair<int, int>> changeStock;

public:
    ChangeCalculator() {
        changeStock = {{50000, 10}, {10000, 10}, {5000, 10}, {1000, 10}, {500, 10}, {100, 10}, {50, 10}, {10, 10}};
    }


    void checkChangeStock() {
        for (pair<int, int> change : changeStock) {
            printf("%d원: %d개\n", change.first, change.second);
        }
    }

    void addChangeStock(int value, int quantity) {
        for (pair<int, int> &change : changeStock) {
            if (change.first == value) {
                change.second += quantity;
                return;
            }
        }
        changeStock.push_back({value, quantity});
    }


    bool checkChange(int price, int paid) {
        int totalChange = 0;
        for(pair<int, int> change : changeStock){
            int value = change.first;
            int quantity = change.second;
            totalChange += value * quantity;

        }

        //거스름돈을 주어야 할 금액이 거스름돈의 총합보다 크면 false, 아니면 true
        if(paid - price < totalChange){
            return true;
        } else{
            return false;
        }
    }

    void calculateChange(int price, int paid){
        if(!checkChange(price, paid)){
            printf("거스름돈이 부족합니다.\n");
            return;
        }

        int change = paid - price;

        for(pair<int, int> &changeStock : changeStock){
            int value = changeStock.first;
            int quantity = changeStock.second;

            if(change >= value * quantity){
                change -= value * quantity;
                changeStock.second = 0;
            }else{
                int changeQuantity = change / value;
                if(changeQuantity > quantity){
                    changeQuantity = quantity;
                }
                change -= value * changeQuantity;
                changeStock.second -= changeQuantity;
            }
        }
    }

};

//음료수가 담겨있는 자판기 역할 클래스
class VendingMachine : public ChangeCalculator {
private:
    list<pair<string, int>> productStock;
public:
    //음료수 정보는 이름, 가격으로 이루어져 있음
    VendingMachine() {
        productStock = {{"Coke", 1000}, {"Cider", 1000}, {"Fanta", 1500}};
    }

    void printMenu(){
        for(pair<string, int> product : productStock){
            string name = product.first;
            int price = product.second;
            printf("%s: %d원\n", name.c_str(), price);
        }
    }

    void purchaseDrink(string drinkname, int paid){
        for(pair<string, int> &product : productStock){
            string name = product.first;
            int price = product.second;

            if(drinkname == name){
                if(paid < price){
                    printf("돈이 부족합니다.\n");
                    return;
                }
                if(checkChange(price, paid)){
                    calculateChange(price, paid);
                    printf("%s 구매 완료\n", drinkname.c_str());
                    return;
                }else{
                    printf("거스름돈이 부족합니다.\n");
                    return;
                }
            }
        }
        printf("해당 제품이 없습니다.\n");
    }


};


int Menu(){
    cout << "1. 음료수 구매" << endl;
    cout << "2. 월간 매출 보고서 확인"<< endl;
    cout << "3. 일간 매출 보고서 확인" << endl;
    cout << "4. 거스름돈 투입" << endl;
    cout << "5.종료"<< endl;

    cout << "메뉴를 선택하세요: ";
    int menu;
    cin >> menu;

    return menu;


}

//일간, 월간 매출보고서 만들면 됨
int main(){
    VendingMachine vendingMachine;

    while (1){
        int menu = Menu();
        if(menu == 1){
            string drinkname;
            int paid;
            vendingMachine.printMenu();
            cout << "구매할 음료수를 입력하세요: ";
            cin >> drinkname;
            cout << "돈을 투입하세요: ";
            cin >> paid;
            vendingMachine.purchaseDrink(drinkname, paid);
        }else if(menu == 2){
            printf("월간 매출 보고서\n");
            vendingMachine.checkChangeStock();
        }else if(menu == 3){
            printf("일간 매출 보고서\n");
        }else if(menu == 4){
            int value, quantity;
            cout << "투입할 거스름돈의 금액을 입력하세요: ";
            cin >> value;
            cout << "투입할 거스름돈의 개수를 입력하세요: ";
            cin >> quantity;
            vendingMachine.addChangeStock(value, quantity);
        }else if(menu == 5){
            break;
        }
    }


    return 0;
}