bool cardInserted() {
  bool card = false;
  if (digitalRead(CD)) {
    Serial.println("Card Inserted!");
    card = true;
  } else {
    card = false;
  }
  return card;
}
