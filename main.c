//
//  main.c
//  am-here
//
//  Created by Joseph Levine on 2/12/20.
//  Copyright © 2020 Flatt Matt Fan Club. All rights reserved.
//

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <time.h>
#include <unistd.h>

const char* home() {
  struct passwd* pw = getpwuid(getuid());
  return pw->pw_dir;
}

const char* isoDate() {
  time_t rawtime;
  struct tm* timeinfo;
  char* buffer = malloc(11 * sizeof(char));

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, 11, "%Y-%m-%d", timeinfo);
  return buffer;
}

const char* cstTimeNow() {
  time_t rawTime;
  struct tm* timeInfo;
  char* buffer = malloc(7 * sizeof(char));

  time(&rawTime);
  timeInfo = localtime(&rawTime);

  strftime(buffer, 7, "%R\n", timeInfo);
  return buffer;
}

const char* bootTime() {
  const int numberOfKernelParameters = 2;
  int kernelCall[numberOfKernelParameters] = {CTL_KERN, KERN_BOOTTIME};
  size_t size;
  struct timeval bootTime;

  size = sizeof(bootTime);
  int call =
      sysctl(kernelCall, numberOfKernelParameters, &bootTime, &size, NULL, 0);
  if (call != -1) {
    time_t bootSeconds = bootTime.tv_sec;
    struct tm* timeInfo = localtime(&bootSeconds);
    char* buffer = malloc(7 * sizeof(char));
    strftime(buffer, 7, "%R\n", timeInfo);
    return buffer;
  }
  return NULL;
}

const char* dirForToday() {
  const char* homeDir = home();
  const char* intermediateDir = "/Documents/am-here/";
  const char* date = isoDate();
  size_t totalLength =
      strlen(homeDir) + strlen(intermediateDir) + strlen(date) + 1;
  char* path = malloc(totalLength * sizeof(char));
  snprintf(path, totalLength, "%s%s%s", homeDir, intermediateDir, date);
  return (const char*)path;
}

void go() {
  struct stat st = {0};
  const char* path = dirForToday();
  unsigned long pathLength = strlen(path);
  if (stat(path, &st)) {
    mkdir(path, 0755);
    char withStartFile[pathLength + 7];
    snprintf(withStartFile, pathLength + 7, "%s/start", path);
    FILE* start = fopen(withStartFile, "w");
    fputs(bootTime(), start);
    fclose(start);
  }
  char withStartFile[pathLength + 5];
  snprintf(withStartFile, pathLength + 5, "%s/end", path);
  FILE* start = fopen(withStartFile, "w");
  fputs(cstTimeNow(), start);
  fclose(start);
}

int main(int argc, const char* argv[]) {
  // insert code here...
  go();
  return 0;
}
