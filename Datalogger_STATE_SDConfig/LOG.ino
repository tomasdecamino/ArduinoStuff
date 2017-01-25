void logData() {

  timestamp = getTimestamp();
  // get sensor data -- this could have some preprocessing/filtering built-in
  // save data to file
  logfile.print(timestamp); 
  logfile.print(",");
  logfile.print(uv.readVisible()); 
  logfile.print(",");
  logfile.print(uv.readIR()); logfile.print(",");
  logfile.println(uv.readUV());
  logfile.flush();
  if (logfile.size() > 10000000) { // if filesize is more than 10M then create a new file
    logfile.close();
    stage = NEW;
  }
  digitalWrite(SD_LED, HIGH); // quick blink of the led to show activity
  delay(40);
  digitalWrite(SD_LED, LOW);
}
