bool initSDCard() { //inits SD Card, open new file and inserts header
  bool success = false;
  if (!SD.begin(CS)) {
    success = false;
  } else {
    char filename[15];
    strcpy(filename, "LOG00.TXT");
    for (uint8_t i = 0; i < 100; i++) {
      filename[3] = '0' + i / 10;
      filename[4] = '0' + i % 10;
      // create if does not exist, do not open existing, write, sync after write
      if (! SD.exists(filename)) {
        break;
      }
    }
    logfile = SD.open(filename, FILE_WRITE);

    //Create header
    logfile.println("time,sensor1,sensor2,sensor3");
    logfile.flush();
    success = true;
  }
  return success;
}

