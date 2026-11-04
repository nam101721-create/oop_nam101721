#include <iostream>
#include <string>
using namespace std;

class Vehicle {
    private:
        int vehicleID, entryTime, parkingDuration;
        string vehicleType;
        double parkingFee;
        bool isOccupied;
    public:
        Vehicle();

        Vehicle(int vehicleID, string vehicleType, int entryTime, int parkingDuration, double parkingFee, bool isOccupied);

        int getVehicleID();
        string getVehicleType();
        int getEntryTime();
        int getParkingDuration();
        double getParkingFee();
        bool getIsOccupied();

        void setVehicleID(int vehicleID);
        void setVehicleType(string vehicleType);
        void setEntryTime(int entryTime);
        void setParkingDuration(int parkingDuration);
        void setParkingFee(double parkingFee);
        void setIsOccupied(bool isOccupied);

        void calculateFee();
        void display();
};

Vehicle::Vehicle() {vehicleID = 0; vehicleType = ""; entryTime = 0; parkingDuration = 0; parkingFee = 0.0; isOccupied = false;}

Vehicle::Vehicle(int vehicleID, string vehicleType, int entryTime, int parkingDuration, double parkingFee, bool isOccupied) {
    this->vehicleID = vehicleID;
    this->vehicleType = vehicleType;
    this->entryTime = entryTime;
    this->parkingDuration = parkingDuration;
    this->parkingFee = parkingFee;
    this->isOccupied = isOccupied;
}

int Vehicle::getVehicleID() {return vehicleID;}
string Vehicle::getVehicleType() {return vehicleType;}
int Vehicle::getEntryTime() {return entryTime;}
int Vehicle::getParkingDuration() {return parkingDuration;}
double Vehicle::getParkingFee() {return parkingFee;}
bool Vehicle::getIsOccupied() {return isOccupied;}

void Vehicle::setVehicleID(int vehicleID) {this->vehicleID = vehicleID;}
void Vehicle::setVehicleType(string vehicleType) {this->vehicleType = vehicleType;}
void Vehicle::setEntryTime(int entryTime) {this->entryTime = entryTime;}
void Vehicle::setParkingDuration(int parkingDuration) {this->parkingDuration = parkingDuration;}
void Vehicle::setParkingFee(double parkingFee) {this->parkingFee = parkingFee;}
void Vehicle::setIsOccupied(bool isOccupied) {this->isOccupied = isOccupied;}

void Vehicle::calculateFee(){
    double price = 0;

    if (vehicleType == "Car" || vehicleType == "car" || vehicleType == "CAR") {
        price = 6000;
    } else if (vehicleType == "Motorcycle" || vehicleType == "motorcycle" || vehicleType == "MOTORCYCLE") {
        price = 4000;
    } else if (vehicleType == "bicycle" || vehicleType == "Bicycle" || vehicleType == "BICYCLE") {
        price = 2000;
    }

    bool isPeakHour = (entryTime >= 6 && entryTime < 10) || (entryTime >= 15 && entryTime < 19);
    parkingFee = 0;
    for (int i = 0; i < parkingDuration; i++){
        if (i < 2){
            parkingFee += price * (isPeakHour ? 1.3 : 0.95);
        } else {
            parkingFee += price * 0.9;
        }
    }
}

void Vehicle::display(){
    cout << "Ma xe: " << vehicleID << endl;
    cout << "Loai xe (Car, Motorbike, Bicycle): " << vehicleType << endl;
    cout << "Gio vao " << entryTime << endl;
    cout << "Thoi gian do xe: " << parkingDuration << endl;
    cout << "Tien gui xe: " << parkingFee << endl;
    cout << "Trang thai: " << isOccupied << endl;
}

class ParkingLot{
    private:
        int parkID;
        char size;
        Vehicle vehicle1, vehicle2, vehicle3;
        bool hasVehicle1, hasVehicle2, hasVehicle3;
    public:
        ParkingLot();
        ParkingLot(int parkID, char size);
        int getParkID();
        char getSize();
        bool addVehicle(const Vehicle& v);
        bool removeVehicle(int vID);
        void displayLotInfo();
};

ParkingLot::ParkingLot(){parkID = 0; size = 'S'; hasVehicle1 = false; hasVehicle2 = false; hasVehicle3 = false;}

ParkingLot::ParkingLot(int parkID, char size){
    this->parkID = parkID;
    this->size = size;
    hasVehicle1 = false;
    hasVehicle2 = false;
    hasVehicle3 = false;
}

int ParkingLot::getParkID(){return parkID;}

char ParkingLot::getSize(){return size;}

bool ParkingLot::addVehicle(const Vehicle& v){
    int cap = (size == 'S') ? 1 : (size == 'M') ? 2 : 3;
    if (cap >= 1 && !hasVehicle1){
        vehicle1 = v;
        vehicle1.setIsOccupied(true);
        hasVehicle1 = true;
        return true;
    } else if (cap >= 2 && !hasVehicle2){
        vehicle2 = v;
        vehicle2.setIsOccupied(true);
        hasVehicle2 = true;
        return true;
    } else if (cap == 3 && !hasVehicle3){
        vehicle3 = v;
        vehicle3.setIsOccupied(true);
        hasVehicle3 = true;
        return true;
    }
    return false;
}

bool ParkingLot::removeVehicle(int vID){
    if (hasVehicle1 && vehicle1.getVehicleID() == vID) {
        if (hasVehicle2) {
            vehicle1 = vehicle2;
            if (hasVehicle3) {
                vehicle2 = vehicle3;
                vehicle3 = Vehicle();
                hasVehicle3 = false;
            }else {
                vehicle2 = Vehicle();
                hasVehicle2 = false;
            }
        }else {
            vehicle1 = Vehicle();
            hasVehicle1 = false;
        }
        return true;
    }
    if (hasVehicle2 && vehicle2.getVehicleID() == vID) {
        if (hasVehicle3) {
            vehicle2 = vehicle3;
            vehicle3 = Vehicle();
            hasVehicle3 = false;
        } else {
            vehicle2 = Vehicle();
            hasVehicle2 = false;
        }
        return true;
    }
    if (hasVehicle3 && vehicle3.getVehicleID() == vID) {
        vehicle3 = Vehicle();
        hasVehicle3 = false;
        return true;
    }
    return false;
}

void ParkingLot::displayLotInfo(){
    cout << "Ma bai xe: " << parkID << endl;
    cout << "Kich thuoc: " << size << endl;
    if (hasVehicle1) {
        vehicle1.display();
    }

    if (hasVehicle2) {
        vehicle2.display();
    }

    if (hasVehicle3) {
        vehicle3.display();
    }
}

class SystemInterface{
    private:
        ParkingLot parkingLot1, parkingLot2, parkingLot3;
        bool hasLot1, hasLot2, hasLot3;
    public:
        SystemInterface();
        void runMenu();
};

SystemInterface::SystemInterface() {
    hasLot1 = false;
    hasLot2 = false;
    hasLot3 = false;
}

void SystemInterface::runMenu(){
    int choice;

    while (true) {
        cout << "\n========== QUAN LY BAI DO XE ==========";
        cout << "\n1. Tao bai do xe moi.";
        cout << "\n2. Them xe vao bai xe.";
        cout << "\n3. Xoa mot bai xe.";
        cout << "\n4. Xoa xe ra khoi bai xe.";
        cout << "\n5. Hien thi danh sach tat ca bai xe.";
        cout << "\n6. Hien thi danh sach xe theo bai xe";
        cout << "\n7. Liet ke xe theo loai phuong tien";
        cout << "\n8. Xem bao cao tom tat phi do xe trung binh.";
        cout << "\n9. Thoat.";
        cout << "\nNhap lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:{
            int id;
            char size;
            cout << "Nhap ma bai xe: ";
            cin >> id;
            cout << "Nhap kich thuoc cua bai xe: ";
            cin >> size;

            if (!hasLot1) {
                parkingLot1 = ParkingLot(id, size);
                hasLot1 = true;
            } else if (!hasLot2) {
                parkingLot2 = ParkingLot(id, size);
                hasLot2 = true;
            } else if (!hasLot3) {
                parkingLot3 = ParkingLot(id, size);
                hasLot3 = true;
            } else {
                cout << "Full slot." << endl;
            } break;
        }
        case 2:{
            int id, time, duration;
            string type;

            cout << "Nhap ID cua xe: ";
            cin >> id;
            cout << "Nhap loai xe(Car, Motocycle, Bicycle): ";
            cin >> type;
            cout << "Nhap thoi gian vao: ";
            cin >> time;
            cout << "Nhap tong thoi gian do: ";
            cin >> duration;

            Vehicle v(id, type, time, duration, 0, false);
            v.calculateFee();
            bool ok = false;
            if (hasLot1 && !ok){
                ok = parkingLot1.addVehicle(v);
            }
            if (hasLot2 && !ok){
                ok = parkingLot2.addVehicle(v);
            }
            if (hasLot3 && !ok){
                ok = parkingLot3.addVehicle(v);
            }
            if (ok){
                cout << "Them xe thanh cong.";
            } else {
                cout << "Khong con cho trong.";
            } break;
        }

        case 3:{
            int id;
            cout << "Nhap ma bai xe can xoa: ";
            cin >> id;
            if (hasLot1 && parkingLot1.getParkID() == id) {
                parkingLot1 = parkingLot2;
                hasLot1 = hasLot2;
                parkingLot2 = parkingLot3;
                hasLot2 = hasLot3;
                hasLot3 = false;
                cout << "Xoa bai xe thanh cong.";
            } else if (hasLot2 && parkingLot2.getParkID() == id) {
                parkingLot2 = parkingLot3;
                hasLot2 = hasLot3;
                hasLot3 = false;
                cout << "Xoa bai xe thanh cong.";
            } else if (hasLot3 && parkingLot3.getParkID() == id) {
                parkingLot3 = ParkingLot();
                hasLot3 = false;
                cout << "Xoa bai xe thanh cong.";
            } else {
                cout << "Khong tim thay bai xe.";
            } break;
        }
        
        case 4:{
            int id;
            cout << "Nhap ID cua xe can xoa: ";
            cin >> id;
            bool ok = false;
            if (hasLot1 && !ok){
                ok = parkingLot1.removeVehicle(id);
            }
            if (hasLot2 && !ok){
                ok = parkingLot2.removeVehicle(id);
            }
            if (hasLot3 && !ok){
                ok = parkingLot3.removeVehicle(id);
            }
            if (ok){
                cout << "Xoa xe thanh cong.";
            } else {
                cout << "Khong tim thay xe.";
            } break;
        }

        case 5:{
            if (hasLot1) parkingLot1.displayLotInfo();
            if (hasLot2) parkingLot2.displayLotInfo();
            if (hasLot3) parkingLot3.displayLotInfo();
            break;
        }

        case 6:{
            int id;
            cout << "Nhap ma bai xe: ";
            cin >> id;
            if (hasLot1 && parkingLot1.getParkID() == id) {
                parkingLot1.displayLotInfo();
            } else if (hasLot2 && parkingLot2.getParkID() == id) {
                parkingLot2.displayLotInfo();
            } else if (hasLot3 && parkingLot3.getParkID() == id) {
                parkingLot3.displayLotInfo();
            } else {
                cout << "Khong tim thay bai xe.";
            } break;
        }

        case 7:{
            string type;
            cout << "Nhap loai xe (Car, Motorcycle, Bicycle): ";
            cin >> type;
            if (hasLot1) {
                if ((parkingLot1.getSize() == 'S' && parkingLot1.getSize() == 'M') || (parkingLot1.getSize() == 'L')) {
                    parkingLot1.displayLotInfo();
                }
            }
            if (hasLot2) {
                if ((parkingLot2.getSize() == 'S' && parkingLot2.getSize() == 'M') || (parkingLot2.getSize() == 'L')) {
                    parkingLot2.displayLotInfo();
                }
            }
            if (hasLot3) {
                if ((parkingLot3.getSize() == 'S' && parkingLot3.getSize() == 'M') || (parkingLot3.getSize() == 'L')) {
                    parkingLot3.displayLotInfo();
                }
            } break;
        }
        case 8:{

        }
        
        case 9:
            return;

        default:
            cout << "Lua chon khong hop le.";
        }
    }
}

int main(){
    SystemInterface sys;
    sys.runMenu();
    return 0;
}