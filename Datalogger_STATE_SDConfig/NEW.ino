bool initSDCard() { //inits SD Card, checks config file, open new file and inserts header
  bool success = false;
  if (!SD.begin(CS)) {
    success = false;
  } else {
    // Read settigs from config file
    readSDSettings();
    //Create new LOG file
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
    logfile.println("timestamp,visible,infrarojo,ultravioleta");
    logfile.flush();
    success = true;
  }
  return success;
}

