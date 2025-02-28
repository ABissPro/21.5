#include <iostream>
#include <vector>
#include <string>

enum RoomType {
    BEDROOM,
    KITCHEN,
    BATHROOM,
    CHILDRENS,
    LIVING_ROOM
};

enum BuildingType {
    HOUSE,
    GARAGE,
    BARN,
    BATHHOUSE
};

struct Room {
    RoomType type;
    double area;
};

struct Floor {
    std::vector<Room> rooms;
    double ceiling_height;
};

struct Building {
    BuildingType type;

    //Общие поля
    double area;
    bool has_stove;

    //специфичные для дома
    std::vector<Floor> floors;
};

struct Plot {
    int number;
    std::vector<Building> buildings;
    double total_area;
};

struct Village {
    std::vector<Plot> plots;
    double total_area;
};

Room input_room() {
    Room room;
    int type;
    std::cout << "Тип комнаты (0-спальня, 1-кухня, 2-ванная, 3-детская, 4-гостиная): ";
    std::cin >> type;
    room.type = static_cast<RoomType>(type);
    std::cout << "Площадь комнаты: ";
    std::cin >> room.area;
    return room;
}

Building input_house() {
    Building house;
    house.type = HOUSE;
    house.area = 0;

    std::cout << "Есть ли печь (1-да, 0-нет): ";
    std::cin >> house.has_stove;

    int floors_count;
    do {
        std::cout << "Количество этажей (1-3): ";
        std::cin >> floors_count;
    } while (floors_count < 1 || floors_count > 3);

    for (int i = 0; i < floors_count; ++i) {
        Floor floor;
        std::cout << "Этаж " << i + 1 << ":\n";
        std::cout << "Высота потолков: ";
        std::cin >> floor.ceiling_height;

        int rooms_count;
        do {
            std::cout << "Количество комнат (2-4): ";
            std::cin >> rooms_count;
        } while (rooms_count < 2 || rooms_count > 4);

        for (int j = 0; j < rooms_count; ++j) {
            Room room = input_room();
            floor.rooms.push_back(room);
            house.area += room.area;
        }
        house.floors.push_back(floor);
    }
    return house;
}

Building create_building(BuildingType type) {
    Building b;
    b.type = type;
    b.area = 0;
    b.has_stove = false;

    switch (type) {
    case HOUSE:
        return input_house();

    case GARAGE:
        std::cout << "Площадь гаража: ";
        std::cin >> b.area;
        break;

    case BARN:
        std::cout << "Площадь сарая: ";
        std::cin >> b.area;
        break;

    case BATHHOUSE:
        std::cout << "Площадь бани: ";
        std::cin >> b.area;
        std::cout << "Есть ли печь (1-да, 0-нет): ";
        std::cin >> b.has_stove;
        break;
    }
    return b;
}

Plot input_plot(int plot_number) {
    Plot plot;
    plot.number = plot_number;

    int buildings_count;
    std::cout << "\nКоличество построек на участке: ";
    std::cin >> buildings_count;

    plot.total_area = 0;
    for (int i = 0; i < buildings_count; ++i) {
        int type;
        std::cout << "\nТип постройки (0-дом, 1-гараж, 2-сарай, 3-баня): ";
        std::cin >> type;

        Building building = create_building(static_cast<BuildingType>(type));
        plot.total_area += building.area;
        plot.buildings.push_back(building);
    }
    return plot;
}

int main() {
    system("chcp 1251"); // Установить кодировку
    Village village;

    int plots_count;
    std::cout << "Введите количество участков в посёлке: ";
    std::cin >> plots_count;

    village.total_area = 0;
    for (int i = 0; i < plots_count; ++i) {
        std::cout << "\nУчасток #" << i + 1 << ":\n";
        Plot plot = input_plot(i + 1);
        village.plots.push_back(plot);
        village.total_area += plot.total_area;
    }

    std::cout << "\n\nОбщая площадь всех построек в посёлке: "
        << village.total_area << " кв.м.\n";

    return 0;
}