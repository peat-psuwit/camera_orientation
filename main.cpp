/*
 * A simple utility to check how libhybris & QT detect cameras on the device.
 * 
 * Copyright 2019 Ratchanan Srirattanamet
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

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
