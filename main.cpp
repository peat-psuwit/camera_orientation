#include <stdio.h>
#include <stdlib.h>

#include <hybris/camera/camera_compatibility_layer.h>
#include <hybris/camera/camera_compatibility_layer_capabilities.h>

#include <QCameraInfo>

void printDeviceName() {
  printf("This device is: ");
  fflush(stdout);
  system("getprop ro.product.model");
}

void printCamInfoHybris () {
  int camCount = android_camera_get_number_of_devices();
  int deviceId;

  printf("According to libhybris, this device has %d camera(s).\n", camCount);

  for (deviceId=0; deviceId<camCount; deviceId++) {
    int facing, orientation;

    int result = android_camera_get_device_info(deviceId,
                                                &facing,
                                                &orientation);

    if (result != 0)
      printf("Camera %d: unable to get camera info.\n", deviceId);
    else
      printf("Camera %d: facing = %d, orientation = %d.\n",
             deviceId,
             facing,
             orientation);
  }
}

void printCamInfoQT() {
  const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
  int i = 0;

  printf("According to QT, this device has %d camera(s).\n",
                                                   availableCameras.length());

  for (const QCameraInfo &cameraInfo : availableCameras) {
    printf("Camera %d: position() = %d, orientation() = %d.\n",
           i,
           cameraInfo.position(),
           cameraInfo.orientation());
    i++;
  }
}

int main(int /* argc */, char **/* argv */) {
  printDeviceName();
  putchar('\n');

  printCamInfoHybris();
  putchar('\n');

  printCamInfoQT();
  putchar('\n');

  return 0;
}
