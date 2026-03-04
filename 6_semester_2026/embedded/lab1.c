// https://gist.github.com/mianbilal10/4023baa141e66b1ff20d14de93c7b8a6
String const morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.",
    "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
    ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

int BASE = 48;
int DOT = 1 * BASE;
int DASH = 3 * BASE;
int SPACE = 1 * BASE;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    char chr = Serial.read();
    if (chr == '\\') {
      Serial.write("new base speed\n");
      char buffer[5];
      Serial.readBytes(buffer, 4);
      BASE = atoi(buffer);
      Serial.write("new base speed set ");
      Serial.println(BASE);
      return;
    }
    else if (chr == ' ') {
      delay(7*BASE);
      return;
    }

    Serial.write(chr);
    Serial.write('\n');

    // >>> ord('a')
    // 97
    // >>> ord('z')
    // 122

    if (chr >= 97 && chr <= 122) {
      String res = morseCode[chr-97];
      for (size_t i = 0; i <= res.length(); ++i) {
        if (res[i] == '.') {
          Serial.write(" dot\n");
          digitalWrite(LED_BUILTIN, HIGH);
          delay(DOT);
          digitalWrite(LED_BUILTIN, LOW);
          delay(SPACE);
        } 
        else if (res[i] == '-') {
          Serial.write(" dash\n");
          digitalWrite(LED_BUILTIN, HIGH);
          delay(DASH);
          digitalWrite(LED_BUILTIN, LOW);
          delay(SPACE);
        }
      }
      delay(3*BASE);
    }
  }                   
}
