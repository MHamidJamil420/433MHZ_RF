String getString() {
  String sdata = "";
  char ch = '0';
  bool condit = true;
  while (condit) {
    // if (Serial.available() > 0)
    // {
    ch = Serial.read(); // get the character
    delay(20);
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
        (ch >= '0' && ch <= '9') || (ch == '=')) {
      sdata += ch;

    } else if (ch == '!') {
      Serial.println("Bypassed");
      loop();
      return "NULL";
    } else if (ch == '~') {
      Serial.println("Sr we got ");
      Serial.println(sdata);
      condit = false;
      // FileNameLoop = sdata;
    } else if (ch == '`') {
      Serial.println("Str cleared");
      sdata = "";
      // Serial.println(sdata);
      // condit = false;
      // FileNameLoop = sdata;
    }
    // }
  }
  return sdata;
}