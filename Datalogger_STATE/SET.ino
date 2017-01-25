const byte seconds = 0;
const byte minutes = 29;
const byte hours = 6;
const byte day = 4;
const byte month = 7;
const byte year = 16;

void setClock() {
  
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);
}
