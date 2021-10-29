
#include <FastLED.h>
#include <DS3231.h>



/*!
 * \brief FastLED defines
 */
#define NUM_LEDS 110  
#define DATA_PIN 13


/*!
 * \brief static FastLED component
 */
static CRGB leds[NUM_LEDS];


/*!
 * \brief static rtc component
 */
static DS3231  rtc(SDA, SCL);


/*!
 * \brief soldered LED board, need to substract by 1 when using with LED functions
 */
static constexpr uint8_t display[10][11] =
{
    {1,  20,  21,  40,  41,  60,  61,  80,  81,  100, 101},
    {2,  19,  22,  39,  42,  59,  62,  79,  82,  99,  102},
    {3,  18,  23,  38,  43,  58,  63,  78,  83,  98,  103},
    {4,  17,  24,  37,  44,  57,  64,  77,  84,  97,  104},
    {5,  16,  25,  36,  45,  56,  65,  76,  85,  96,  105},
    {6,  15,  26,  35,  46,  55,  66,  75,  86,  95,  106},
    {7,  14,  27,  34,  47,  54,  67,  74,  87,  94,  107},
    {8,  13,  28,  33,  48,  53,  68,  73,  88,  93,  108},
    {9,  12,  29,  32,  49,  52,  69,  72,  89,  92,  109},
    {10, 11,  30,  31,  50,  51,  70,  71,  90,  91,  110}
};


/*!
 * \brief Definition of all active LEDs for each specific state including size in seperate vector
 */
namespace states {

    /*
    * minute states
    */
    static constexpr uint8_t mState_00[] = { 1, 20, 40, 41, 60, 90, 91, 110 };
    static constexpr uint8_t mState_05[] = { 80, 81, 100, 101, 77, 84, 97, 104 };
    static constexpr uint8_t mState_10[] = { 2, 19, 22, 39, 77, 84, 97, 104 };
    static constexpr uint8_t mState_15[] = { 43, 58, 63, 78, 83, 98, 103 };
    static constexpr uint8_t mState_20[] = { 2, 19, 22, 39, 4, 17, 24, 5, 16, 25, 36 };
    static constexpr uint8_t mState_25[] = { 80, 81, 100, 101, 4, 17, 24, 5, 16, 25, 36 };
    static constexpr uint8_t mState_30[] = { 5, 16, 25, 36 };
    static constexpr uint8_t mState_35[] = { 80, 81, 100, 101, 77, 84, 97, 104, 5, 16, 25, 36 };
    static constexpr uint8_t mState_40[] = { 42, 59, 62, 79, 82, 99, 102, 4, 17, 24 };
    static constexpr uint8_t mState_45[] = { 3, 18, 23, 38, 43, 58, 63, 78, 83, 98, 103 };
    static constexpr uint8_t mState_50[] = { 2, 19, 22, 39, 4, 17, 24, 37 };
    static constexpr uint8_t mState_55[] = { 80, 81, 100, 101, 4, 17, 24 };

    /*
    * pointers to minute states
    */
    const uint8_t* mState[12] =
    {
        mState_00,
        mState_05,
        mState_10,
        mState_15,
        mState_20,
        mState_25,
        mState_30,
        mState_35,
        mState_40,
        mState_45,
        mState_50,
        mState_55
    };

    /*
    * hour states
    */
    static constexpr uint8_t hState_00[] = { 69, 72, 89, 92, 109 };
    static constexpr uint8_t hState_01[] = { 6, 15, 26, 35 };
    static constexpr uint8_t hState_02[] = { 75, 86, 95, 106 };
    static constexpr uint8_t hState_03[] = { 7, 14, 27, 34 };
    static constexpr uint8_t hState_04[] = { 74, 87, 94, 107 };
    static constexpr uint8_t hState_05[] = { 76, 85, 96, 105 };
    static constexpr uint8_t hState_06[] = { 8, 13, 28, 33, 48 };
    static constexpr uint8_t hState_07[] = { 9, 12, 29, 32, 49, 52 };
    static constexpr uint8_t hState_08[] = { 73, 88, 93, 108 };
    static constexpr uint8_t hState_09[] = { 31, 50, 51, 70 };
    static constexpr uint8_t hState_10[] = { 10, 11, 30, 31 };
    static constexpr uint8_t hState_11[] = { 56, 65, 76 };

    /*
    * pointers to hour states
    */
    const uint8_t* hState[12] =
    {
        hState_00,
        hState_01,
        hState_02,
        hState_03,
        hState_04,
        hState_05,
        hState_06,
        hState_07,
        hState_08,
        hState_09,
        hState_10,
        hState_11,
    };

    /*
    * Pointers to state sizes
    */
    static constexpr uint8_t mState_00_size = 8;
    static constexpr uint8_t mState_05_size = 8;
    static constexpr uint8_t mState_10_size = 8;
    static constexpr uint8_t mState_15_size = 7;
    static constexpr uint8_t mState_20_size = 11;
    static constexpr uint8_t mState_25_size = 11;
    static constexpr uint8_t mState_30_size = 4;
    static constexpr uint8_t mState_35_size = 12;
    static constexpr uint8_t mState_40_size = 10;
    static constexpr uint8_t mState_45_size = 11;
    static constexpr uint8_t mState_50_size = 8;
    static constexpr uint8_t mState_55_size = 7;

    /*
    * Pointers to state sizes
    */
    const uint8_t* mStateSizes[12] =
    {
      &mState_00_size,
      &mState_05_size,
      &mState_10_size,
      &mState_15_size,
      &mState_20_size,
      &mState_25_size,
      &mState_30_size,
      &mState_35_size,
      &mState_40_size,
      &mState_45_size,
      &mState_50_size,
      &mState_55_size
    };

    /*
    * Pointers to state sizes
    */
    static constexpr uint8_t hState_00_size = 5;
    static constexpr uint8_t hState_01_size = 4;
    static constexpr uint8_t hState_02_size = 4;
    static constexpr uint8_t hState_03_size = 4;
    static constexpr uint8_t hState_04_size = 4;
    static constexpr uint8_t hState_05_size = 4;
    static constexpr uint8_t hState_06_size = 5;
    static constexpr uint8_t hState_07_size = 6;
    static constexpr uint8_t hState_08_size = 4;
    static constexpr uint8_t hState_09_size = 4;
    static constexpr uint8_t hState_10_size = 4;
    static constexpr uint8_t hState_11_size = 3;

    /*
    * Pointers to state sizes
    */
    const uint8_t* hStateSizes[12] =
    {
      &hState_00_size,
      &hState_01_size,
      &hState_02_size,
      &hState_03_size,
      &hState_04_size,
      &hState_05_size,
      &hState_06_size,
      &hState_07_size,
      &hState_08_size,
      &hState_09_size,
      &hState_10_size,
      &hState_11_size
    };


}


/*!
 * \brief Color class for custom operations
 */
struct Color
{
    Color();
    Color(const uint8_t& r, const uint8_t& g, const uint8_t& b);
    Color(const uint8_t& a);

    Color& operator +=(const Color& other);
    Color& operator -=(const Color& other);
    Color& operator *=(const Color& other);
    Color& operator *=(const uint8_t& i);
    Color& operator /=(const uint8_t& i);

    uint8_t r;
    uint8_t g;
    uint8_t b;
};

/*!
 * \brief init as off
 */
Color::Color() :
    r(0),
    g(0),
    b(0)
{}

/*!
 * \brief init with RBG values
 * \param r red
 * \param g green
 * \param b blue 
 */
Color::Color(const uint8_t& r, const uint8_t& g, const uint8_t& b) :
    r(r), g(g), b(b)
{}

/*!
 * \brief init with HUE value
 * \param a intensitiy
 */
Color::Color(const uint8_t& a) :
    r(a), g(a), b(a)
{}

Color& Color::operator +=(const Color& other)
{
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

Color& Color::operator  -=(const Color& other)
{
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
}

Color& Color::operator  *=(const Color& other)
{
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
}

Color& Color::operator  *=(const uint8_t& i)
{
    r *= i;
    g *= i;
    b *= i;
    return *this;
}

Color& Color::operator  /=(const uint8_t& i)
{
    r /= i;
    g /= i;
    b /= i;
    return *this;
}

Color operator *(const Color& first, const Color& second)
{
    return Color(first.r * second.r, first.g * second.g, first.b * second.b);
}

Color operator *(const Color& color, const int& f)
{
    return Color(color.r * f, color.g * f, color.b * f);
}

Color operator *(const Color& color, const float& f)
{
    return Color(color.r * f, color.g * f, color.b * f);
}

Color operator /(const Color& color, const int& f)
{
    return Color(color.r / f, color.g / f, color.b / f);
}


/*!
 * \brief static color definitions
 */
static const Color FINAL_COLOR(20,20,20);
static const Color White(100);
static const Color WhiteLess(10);
static const Color Blue(0, 0, 20);
static const Color Red(20, 0, 0);
static const Color Green(0, 20, 0);
static const Color Gold(255,215,0);
static const Color Purple(86,11,173);
static const Color Orange(255,145,173);
static const Color Brown(168,116,88);


/*!
 * \brief set specified LED to given color
 * \param LED_ID position of LED in chain
 * \param color color to change
 */
void turnOnLED(const uint8_t& LED_ID, const Color& color)
{
    leds[LED_ID].setRGB(color.g, color.r, color.b);
}

/*!
 * \brief set specified LEDs to given color
 * \param data pointer to data
 * \param n size of array
 * \param color color to change
 */
void turnOnLED(uint8_t* data, const size_t& n, const Color& color)
{
    for (auto i = 0; i < n; i++)
        turnOnLED(data[i] - 1, color);
}

/*!
 * \brief set all LEDs to given color
 * \param color color to change
 */
void turnOnLED(const Color& color)
{
    for (auto i = 0; i < NUM_LEDS; i++)
        turnOnLED(i, color);
}

/*!
 * \brief set specified LED to off
 * \param color color to change
 */
void turnOffLED(const uint8_t& LED_ID)
{
   leds[LED_ID] = CRGB::Black;
} 

/*!
 * \brief set all LEDs to off
 */
void clearLEDs()
{
    for (uint8_t i = 0; i < 110; i++)
        turnOffLED(i);
    FastLED.show();
}




/*
* Helper Functions
*/
namespace HELPER
{

    /*!
    * \brief Container for 2 uint8_t values to easily compare values
    */
    class pair {
    public:
        pair()
        {}

        pair(uint8_t first, uint8_t second) :
            first(first), second(second)
        {}

        bool operator ==(const pair& other)
        {
            return (first == other.first && second == other.second);
        }

        uint8_t first = -1;
        uint8_t second = -1;
    };


    /*!
    * \brief Function to efficiently (iterations * n) pseudoshuffle an array
    * \param array pointer to data
    * \param n length of data
    * \param iterations number of shuffle iterations
    */
    void shuffleArray(uint8_t* array, const size_t& n, const uint8_t& iterations = 2)
    {
        for (uint8_t k = 0; k < iterations; k++)
        {
            for (uint8_t i = 0; i < n; i++)
            {
                // swap 2 entries
                uint8_t idx = random(0, n);
                uint8_t tmp = array[idx];
                array[idx] = array[i];
                array[i] = tmp;
            }
        }
    }

    /*!
    * \brief Function to search a value in an array
    * \param array pointer to data
    * \param n length of data
    * \param value value to look for in array
    */
    bool inArray(const uint8_t* array, const size_t& n, const uint8_t& value)
    {
        for (uint8_t i = 0; i < n; i++)
            if (array[i] == value)
                return true;
        return false;
    }

    /*!
    * \brief Function to fill array with value
    * \param array pointer to data
    * \param n length of data
    * \param iterations number of shuffle iterations
    */
    void fill_n(uint8_t* array, const size_t& n, const uint8_t& value)
    {
        for (uint8_t i = 0; i < n; i++)
            array[i] = value;
    }

}


/*!
 * \brief Container for 2 pointers to states, used for delivering data to animations
 */
struct Container
{
    /*!
    * \brief Default Constructor
    */
    Container()
    {}


    /*!
    * \brief num of pointers
    * \return num of pointers
    */
    size_t size() const { return m_size; }


    /*!
    * \brief add new data to container
    * \param data pointer to data
    * \param size pointer to data size
    */
    void push_back(const uint8_t* data, const uint8_t* size)
    {
        m_data[m_size] = data;
        m_sizes[m_size] = size;
        m_size++;
    }


    /*!
    * \brief search value in subarrays
    * \param value value to search
    * \return found / not found
    */
    bool inData(const uint8_t& value) const
    {
        for (uint8_t idx = 0; idx < m_size; idx++)
        {
            if (HELPER::inArray(m_data[idx], *m_sizes[idx], value + 1))
                return true;
        }
        return false;
    }


    /*!
    * \brief get subarray size combined
    * \return size of arrays
    */
    size_t getSubSize() const
    {
        size_t n = 0;
        for (uint8_t ix = 0; ix < m_size; ix++)
        {
            n += *m_sizes[ix];
        }
        return n;
    }


    size_t    m_iterator = 0;
    size_t    m_arrayIt = 0;

    size_t    m_size = 0;

    const uint8_t*  m_data[2];
    const uint8_t*  m_sizes[2];
};


/*!
 * \brief virtual base class of a single LED animator
 */
struct Animator
{

    Animator() {}

    Animator(uint8_t m_LED, uint8_t m_steps) :
        m_LED(m_LED),
        m_steps(m_steps * 2)
    {}

    virtual void update() = 0;

    virtual bool isActive() const { return m_counter < m_steps; }

    uint8_t m_counter = 0;
    uint8_t m_steps = 0;
    uint8_t m_LED = 0;
};


/*!
 * \brief linear color animator of single LED, increasing in brightness and not specified fading to black
 */
struct ColorAnimator : public Animator
{

    ColorAnimator()
    {}

    ColorAnimator(uint8_t m_LED, uint8_t m_steps, const Color& color, bool keepOn = false) :
        m_colorstep(color / static_cast<float>(m_steps)),
        m_keepOn(keepOn),
        Animator(m_LED, m_steps)
    {}

    virtual void update() override
    {
        // check if active
        if (!isActive())
            return;

        // check if ascending
        if (m_counter < (m_steps / 2))
            turnOnLED(m_LED, m_colorstep * m_counter);

        else if (!m_keepOn)
            turnOnLED(m_LED, m_colorstep * (m_steps - m_counter - 1));

        m_counter++;
    }

    bool m_keepOn;
    Color m_colorstep;
};


/*!
 * \brief animation base class, specify color as the one to stay on after animation
 */
struct Animation
{
  
  Animation(const Color& color) : m_color(color)
  {}

  ~Animation()
  {}

  virtual void animate(Container& container) 
  {}
  
  void clean() {  clearLEDs(); }

  Color m_color;
};


/*!
 * \brief animation of snake-like visiting of all LEDs
 */
struct Snake : Animation
{
  Snake(const Color& color) : Animation(color){}
    void animate(Container& container) override
    {

        uint8_t start = 0;
        uint8_t active = 0;
        uint8_t end = 110;
        uint8_t anim_steps = 5;
        uint8_t n = end - 1 + (anim_steps * 2);
        ColorAnimator ActiveAnimators[110];

        for (uint8_t i = 0; i < n; i++)
        {
            if (active < end)
            {
                ActiveAnimators[active] = container.inData(active) == true ? ColorAnimator(active, anim_steps, m_color, true) : ColorAnimator(active, anim_steps, Color(random(0, 50), random(0, 50), random(0, 50)));
                active++;
            }

            // update active Animators
            for (uint8_t ac = start; ac < active; ac++)
            {
                if (ActiveAnimators[ac].isActive())
                    ActiveAnimators[ac].update();
                else
                    start++;
            }


            FastLED.show();
            delay(50);
        }
    }
};


/*!
 * \brief animation of random visiting of all LEDs
 */
struct PulseRandom : Animation
{

  PulseRandom(const Color& color) : Animation(color){}

    void animate(Container& container) override
    {

        clearLEDs();

        uint8_t start = 0;
        uint8_t active = 0;
        const uint8_t end = 110;
        const uint8_t anim_steps = 20;

        const uint8_t n = end + anim_steps * 2;

        uint8_t array[end];
        for (uint8_t i = 0; i < end; i++)
            array[i] = i;
        HELPER::shuffleArray(array, end);

        ColorAnimator animators[anim_steps * 2];

        // append all animators
        for (uint8_t idx = 0; idx < n; idx++)
        {
            if (idx < end)
            {
                if (container.inData(array[idx]))
                    animators[active++] = ColorAnimator(array[idx], anim_steps, m_color, true);
                else
                    animators[active++] = ColorAnimator(array[idx], anim_steps, Color(random(0, 50), random(0, 50), random(0, 50)));
            }

            if (active == anim_steps * 2)
                active = 0;
            else if (active > start)
                start++;

            for (uint8_t ix = 0; ix < start; ix++)
                animators[ix].update();

            FastLED.show();
            delay(50);

        }
    }
};


/*!
 * \brief animation of pulsing heart
 */
struct Heart : Animation
{
    Heart() : Animation(Red)
    {}

    void animate(Container& container) override
    {
        clean();
        constexpr uint8_t shape[24] = { 21, 40, 42, 58, 62, 81, 80, 19, 3, 4, 5, 15, 27, 33, 49, 51, 69, 73, 87, 95, 105, 104, 103, 99 };
        constexpr uint8_t anim_steps = 20;

        ColorAnimator animators[24];
        
        for (uint8_t repeat = 0; repeat < 5; repeat++)
        {
            
            for (uint8_t i = 0; i < 24; i++)
                animators[i] = ColorAnimator(shape[i] - 1, anim_steps, m_color);
            
            for (uint8_t i = 0; i < anim_steps * 2; i++)
            {
                for (uint8_t ix = 0; ix < 24; ix++)
                    animators[ix].update();

                FastLED.show();
                delay(50);
            }
        }
    }

};


/*!
 * \brief Animator of a single row
 */
struct RowAnimator
{
    RowAnimator()
    {}

    void setup(uint8_t row, Container& container, const Color& color, bool filter = false)
    {
         m_row = row;
         m_filter = filter;
         
        for (uint8_t ix = 0; ix < 11; ix++)
        {
            if (filter)
                if (container.inData(display[m_row][ix] - 1))
                    Animators[m_active++] = ColorAnimator(display[m_row][ix] - 1, 3, color, true);
            else 
                if (container.inData(display[m_row][ix] - 1))
                    Animators[m_active++] = ColorAnimator(display[m_row][ix] - 1, 3, color, true);
                else
                    Animators[m_active++] = ColorAnimator(display[m_row][ix] - 1, 3, Color(random(0, 30), random(0, 30), random(0, 30)));
        }
    }

    bool hasData() {return m_active > 0;}

    bool isActive() 
    {
      bool flag = false;
      for (uint8_t ix = 0; ix < m_updater; ix++)
            if (Animators[ix].isActive())
            {
                flag = true;
                break;
              }
      return flag;
              
    }

    void update()
    {
        if (m_updater < m_active)
            m_updater++;

        for (uint8_t ix = 0; ix < m_updater; ix++)
            if (Animators[ix].isActive())
                Animators[ix].update();
    }

    ColorAnimator Animators[11];
    uint8_t m_active = 0;
    uint8_t m_updater = 0;
    bool m_filter = false;
    uint8_t m_row = 0;
};


/*!
 * \brief animation of visiting all cells based on RowAnimator
 */
struct RowAnimation : Animation
{
  RowAnimation(const Color& color) : Animation(color){}
    void animate(Container& container) override
    {

        clearLEDs();
        const uint8_t num_animators = 4;

        // need to save memory
        RowAnimator rowAnimators[num_animators];
            
        uint8_t anim_steps = 3;
        uint8_t offset = 5;
        uint8_t steps_per_col = 11 + (anim_steps * 2);
        uint8_t n = 10 * offset + steps_per_col - 5;
        uint8_t start = 0;
        uint8_t active = 0;
        uint8_t curr_row = 0;

        // Animate row
        
        for (uint8_t i = 0; i < n; i++)
        {
           
            // add next actor
            if (i % offset == 0)
            {
                // reset overwrite
                if (start == num_animators)
                    start = 0;

                // is there more rows to add?
                if (curr_row < 10)
                {
                    rowAnimators[start] = RowAnimator();
                    rowAnimators[start].setup(curr_row++, container, m_color);

                    start++;
                    if (active < start)
                        active = start;
                }
              
            }


            // Update Animators
            for (uint8_t ix = 0; ix < active; ix++)
                rowAnimators[ix].update();

            FastLED.show();
            delay(100);
        }   
    }

};


/*!
 * \brief struct to derive current time / set current time / update & check for special days. Add your special days in checkForSpecial() function.
*/
struct CurrentTime
{

  CurrentTime()
  {}

  void setTime(uint8_t day, uint8_t month, uint8_t year, uint8_t hour, uint8_t second, uint8_t minute)
  {
    rtc.setTime(hour, minute, second);
    rtc.setDate(day, month, year);
  }

  void update()
  {
      tt = rtc.getTime();
      year = tt.year;
      month = tt.mon;
      day = tt.date;
      hour = tt.hour;
      minute = tt.min;
      second = tt.sec;
      checkForWT();
  }


  bool checkForSpecial()
  {
    // add all special days here
    const HELPER::pair day1(26, 10);
    const HELPER::pair day2(27, 10);

    // current day
    const HELPER::pair today(day, month);
    
    if (day1 == today)
        return true;
    if (day2 == today)
        return true;
    return false;
  }


  void checkForWT()
  {
    // check early year
    if (month <=3 && day <= 28 && hour <= 2)
    {
        int newHour = hour - 1;
        if (newHour < 0)
            newHour = 11;
        hour = newHour;
    }

    // check late year
    if (month >= 10 && day >= 28 && hour >= 2)
    {
        int newHour = hour - 1;
        if (newHour < 0)
            newHour = 11;
        hour = newHour;
    }
  }


  Time tt;

  uint16_t year = 0;
  uint8_t month = 0;
  uint8_t day = 0;
  uint8_t hour = 0;
  uint8_t minute = 0;
  uint8_t second = 0;
  
  bool isSpecialDate = false;

};


/*!
 * \brief for choosing an animation
*/
bool animation_switch = true;


/*!
 * \brief setup LEDs & RTC
*/
void setup()
{ 
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(80);
  rtc.begin();
}


/*!
 * \brief derive current time and process accordingly
*/
void loop() {


    // update current time
    CurrentTime cTime;
    cTime.update();

    // convert min to query idx
    uint8_t min_idx = static_cast<int> ((float) cTime.minute / 5);

    // get hour idx
    uint8_t hour_idx = min_idx > 2 ? (cTime.hour + 1) % 12 : cTime.hour % 12;

    // create container with data pointers
    Container container;
    container.push_back(states::hState[hour_idx], states::hStateSizes[hour_idx]);
    container.push_back(states::mState[min_idx], states::mStateSizes[min_idx]);

    if (cTime.checkForSpecial())
    {
        // do special
        Heart heart;
        heart.animate(container);
    }

    if (animation_switch)
    {
        // animation 1
        RowAnimation rows(Color(random(0,50),random(0,50),random(0,50)));
        rows.animate(container);
        animation_switch = false;
    }

    else 
    {
        // animation 2
        PulseRandom pulse(Color(random(0,50),random(0,50),random(0,50)));
        pulse.animate(container);
        animation_switch = true;
    }

    // calculate delay until next minute starts
    cTime.update();
    unsigned long wait = 61 - cTime.second;
    delay(wait * 1000);
}