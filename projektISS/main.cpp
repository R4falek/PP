#include <graphics.h>
#include <stdio.h>
#include "cJSON.h"
#include "cJSON.c"
#include <unistd.h>

#define okno_dl 1680
#define okno_sz 840

int main()
{
    initwindow(okno_dl, okno_sz,"Pobieranie lokalizacji Miêdzynarodowej Stacji Kosmicznej ISS");

    while(1)
    {
        system("curl https://api.wheretheiss.at/v1/satellites/25544 > D:/Pulpit/projektISS/plik.txt");
        system("cls");

        FILE *file;
        char buffer[1024];

        file = fopen("plik.txt", "r");

        fread(buffer, 1024, 1, file);
        fclose(file);

        cJSON *parsed_json;
        cJSON *name;
        cJSON *id;
        cJSON *latitude;
        cJSON *longitude;
        cJSON *altitude;
        cJSON *velocity;
        cJSON *visibility;
        cJSON *footprint;
        cJSON *timestamp;
        cJSON *daynum;
        cJSON *solar_lat;
        cJSON *solar_lon;
        cJSON *units;

        parsed_json = cJSON_Parse(buffer);

        name=cJSON_GetObjectItem(parsed_json, "name");
        id=cJSON_GetObjectItem(parsed_json, "id");
        latitude=cJSON_GetObjectItem(parsed_json, "latitude");
        longitude=cJSON_GetObjectItem(parsed_json, "longitude");
        altitude=cJSON_GetObjectItem(parsed_json, "altitude");
        velocity=cJSON_GetObjectItem(parsed_json, "velocity");
        visibility=cJSON_GetObjectItem(parsed_json, "visibility");
        footprint=cJSON_GetObjectItem(parsed_json, "footprint");
        timestamp=cJSON_GetObjectItem(parsed_json, "timestamp");
        daynum=cJSON_GetObjectItem(parsed_json, "daynum");
        solar_lat=cJSON_GetObjectItem(parsed_json, "solar_lat");
        solar_lon=cJSON_GetObjectItem(parsed_json, "solar_lon");
        units=cJSON_GetObjectItem(parsed_json, "units");

        printf("Name: %s\nId: %d\nLatitude: %f\nLongitude: %f\nNaltitude: %f\nVelocity: %f\nVisibility: %s\nFootprint: %f\nTimestamp: %d\nDaynum: %f\nSolar_lat: %f\nSolar-lon: %f\nUnits: %s\n", name->valuestring, id->valueint, latitude->valuedouble, longitude->valuedouble, altitude->valuedouble, velocity->valuedouble, visibility->valuestring, footprint->valuedouble, timestamp->valueint, daynum->valuedouble, solar_lat->valuedouble, solar_lon->valuedouble, units->valuestring);

        double dlugosc=okno_dl/2+(okno_dl*longitude->valuedouble)/360;
        double szerokosc=okno_sz/2-(okno_sz*latitude->valuedouble)/180;

        readimagefile("mapa.jpg", 0, 0, okno_dl, okno_sz);
        setcolor(RED);
        circle(dlugosc,szerokosc,100);
        readimagefile("iss.jpg", dlugosc-50, szerokosc-50, dlugosc-100-50, szerokosc-100-50);

        sleep(1);
    }

    getch();
}
