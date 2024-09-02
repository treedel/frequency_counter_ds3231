#define RST_CNTS 65537

// Flag to notify when new values arrive
volatile bool fresh_data_flag = false;

// Frequency calculation variables
volatile uint8_t overflow_count = 0;

volatile uint16_t count_buffer;
volatile uint8_t overflow_count_buffer;

// Declaring functions
void freqInterruptCallback();
bool isAvailable();
uint32_t getFrequency();

void setup() {
  // For debugging
  Serial.begin(9600);
  Serial.println("High accuracy frequency counter");
  
  // Preparing Counter
  // We use 16 bit timer/counter 1
  TCCR5A = 0;
  TCCR5B = 0;
  TCCR5B = bit(CS52) | bit(CS51) | bit(CS50);
  TIMSK5 = bit(TOIE5);

  // External 1Hz reference
  attachInterrupt(5, freqInterruptCallback, FALLING);

  // Reset counter
  freqInterruptCallback();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (isAvailable()) {
    Serial.println(getFrequency());
  }
}

// ISR For overflows
ISR (TIMER5_OVF_vect) {overflow_count++;}

void freqInterruptCallback() {
  // Disable timer interrupts
  TIMSK5 = 0;

  // Buffer obtained values
  overflow_count_buffer = overflow_count;
  count_buffer = TCNT5;

  fresh_data_flag = true;
  
  // Reset counters
  overflow_count = 0;
  TCNT5 = 0;
}

// Function to tell if new data is available
bool isAvailable() {
  return fresh_data_flag;
}

// Function to calculate and return frequency
uint32_t getFrequency() {
  fresh_data_flag = false;
  return count_buffer + (overflow_count_buffer * RST_CNTS);
}
