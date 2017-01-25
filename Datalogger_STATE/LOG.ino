void logData() {
  // read raw accel/gyro measurements from device
  timestamp = getTimestamp();
  //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.println(timestamp);
  logfile.print(timestamp); 
  logfile.print(",");
  logfile.print(uv.readVisible()); 
  logfile.print(",");
  logfile.print(uv.readIR()); logfile.print(",");
  logfile.println(uv.readUV());

  if (count == 5) { //write to SD Card every 5 samples (saves energy)
    logfile.flush();
    if (logfile.size() > 10000000) { // if filesize is more than 10M then create a new file
      logfile.close();
      stage = NEW;
    }
    count = 0;
  }
  if (millis() % 1000 < 40) { //turn on SD_LED 40 msecs of every second
    digitalWrite(SD_LED, HIGH);
  } else {
    digitalWrite(SD_LED, LOW);
  }
  count ++;
}
