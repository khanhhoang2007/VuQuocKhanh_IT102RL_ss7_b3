
#include <stdio.h>

struct SmartDeviceOld {
    char status;
    double voltage;
    char deviceName[20];
    float current;
    int operatingMinutes;
    double measuredPower;
};

struct SmartDeviceOptimized {
    double voltage;
    double measuredPower;
    int operatingMinutes;
    float current;
    char deviceName[20];
    char status;
};

struct DeviceSensor {
    double voltage;
    float current;
    double measuredPower;
};

struct DeviceInfo {
    int deviceID;
    char deviceName[20];
    char status;
    int operatingMinutes;
};

int main() {
    struct SmartDeviceOld oldDevice;
    struct SmartDeviceOptimized device;
    struct DeviceSensor sensor;
    struct DeviceInfo info;

    double calculatedPower;
    double difference;
    double energyKWh;

    printf("=== SO SANH KICH THUOC STRUCT ===\n");
    printf("Struct cu: %zu bytes\n", sizeof(oldDevice));
    printf("Struct toi uu: %zu bytes\n", sizeof(device));
    printf("Struct long nhau - sensor: %zu bytes\n",
           sizeof(sensor));
    printf("Struct long nhau - info: %zu bytes\n",
           sizeof(info));

    printf("\n=== NHAP THONG TIN THIET BI ===\n");

    printf("Nhap ma thiet bi: ");
    if (scanf("%d", &info.deviceID) != 1) {
        printf("Loi: Ma thiet bi khong hop le!\n");
        return 1;
    }

    printf("Nhap ten thiet bi: ");
    if (scanf(" %19[^\n]", info.deviceName) != 1) {
        printf("Loi: Ten thiet bi khong hop le!\n");
        return 1;
    }

    printf("Nhap trang thai (0: Tat, 1: Bat): ");
    if (scanf(" %c", &device.status) != 1) {
        printf("Loi: Khong doc duoc trang thai!\n");
        return 1;
    }

    if (device.status != '0' && device.status != '1') {
        printf("Loi: Trang thai chi duoc nhap 0 hoac 1!\n");
        return 1;
    }

    printf("Nhap dien ap (V): ");
    if (scanf("%lf", &sensor.voltage) != 1) {
        printf("Loi: Dien ap khong hop le!\n");
        return 1;
    }

    printf("Nhap dong dien (A): ");
    if (scanf("%f", &sensor.current) != 1) {
        printf("Loi: Dong dien khong hop le!\n");
        return 1;
    }

    printf("Nhap cong suat do duoc (W): ");
    if (scanf("%lf", &sensor.measuredPower) != 1) {
        printf("Loi: Cong suat khong hop le!\n");
        return 1;
    }

    printf("Nhap thoi gian hoat dong (phut): ");
    if (scanf("%d", &info.operatingMinutes) != 1) {
        printf("Loi: Thoi gian khong hop le!\n");
        return 1;
    }

    /* Kiem tra du lieu */
    if (sensor.voltage <= 0 ||
        sensor.current < 0 ||
        sensor.measuredPower < 0 ||
        info.operatingMinutes < 0) {
        printf("\nLoi: Du lieu cam bien khong hop le!\n");
        return 1;
    }

    /* Tinh cong suat theo dien ap va dong dien */
    calculatedPower = sensor.voltage * sensor.current;

    printf("\n=== KET QUA PHAN TICH ===\n");

    printf("Ma thiet bi: %d\n", info.deviceID);
    printf("Ten thiet bi: %s\n", info.deviceName);
    printf("Trang thai: %s\n",
           device.status == '1' ? "BAT" : "TAT");

    printf("Cong suat tinh toan: %.2f W\n", calculatedPower);
    printf("Cong suat do duoc: %.2f W\n",
           sensor.measuredPower);

    /* Kiem tra sai lech cong suat */
    difference = sensor.measuredPower - calculatedPower;

    if (difference < 0) {
        difference = -difference;
    }

    if ((calculatedPower == 0 && sensor.measuredPower != 0) ||
        (calculatedPower > 0 &&
         difference > calculatedPower * 0.05)) {
        printf("Canh bao: Cam bien cong suat bao sai lech!\n");
    } else {
        printf("Cam bien cong suat: Binh thuong.\n");
    }

    /* Kiem tra qua tai */
    if (sensor.current > 30.0f ||
        sensor.measuredPower > 6600.0) {
        printf("CANH BAO: QUA TAI NGUY HIEM!\n");
    }

    /* Kiem tra ro ri dien */
    if (device.status == '0' && sensor.current > 0.05f) {
        printf("CANH BAO: RO RI DIEN HOAC TAI AN!\n");
    }

    /* Tinh dien nang, doi phut sang gio bang phep chia so thuc */
    energyKWh = sensor.measuredPower
              * ((double)info.operatingMinutes / 60.0)
              / 1000.0;

    printf("Thoi gian hoat dong: %d phut\n",
           info.operatingMinutes);
    printf("Dien nang tieu thu: %.6f kWh\n", energyKWh);

    return 0;
}