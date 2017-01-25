bool cardInserted() {
  bool card = false;
  if (digitalRead(CD)) {
    card = true;
  } else {
    card = false;
  }
  return card;
}
