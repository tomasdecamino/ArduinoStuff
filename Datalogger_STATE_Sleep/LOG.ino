void logData() {

  timestamp = getTimestamp();
  int sensor1 = analogRead(A0);
  int sensor2 = analogRead(A1);
  int sensor3 = analogRead(A2);
  Serial.println(timestamp);
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
  digitalWrite(SD_LED, HIGH);
  delay(40);
  digitalWrite(SD_LED, LOW);
}
