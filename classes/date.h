#ifndef date_h
#define date_h
#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include <map>
using namespace std;
using namespace chrono;
const hours UTC{3}; //set timezone (Moscow +3)
class Date
{
private:
    system_clock::time_point time; //date + time
    year_month_day current_date;  //day month year
    weekday current_weekday; //day of week
    hh_mm_ss <seconds> current_time; //hours minutes seconds
public:
    Date () = default;
    Date (const year_month_day& ymd) 
    {current_date = ymd; current_weekday = weekday(current_date);}
    void update_time() 
    {
        time = floor<seconds>(system_clock::now()) + UTC; //date + time with UTC
        current_date = floor<days>(time); //get date
        current_weekday = weekday(current_date); //get day of week
        current_time = hh_mm_ss(duration_cast<seconds>(time - floor<days>(time))); //get time
    }
    static system_clock::time_point sys_t()
    {
        return floor<seconds>(system_clock::now()) + UTC;
    }
    static year_month_day sys_date()
    {
        return floor<days>(sys_t());
    }
    static hh_mm_ss<seconds> sys_time()
    {
        hh_mm_ss<seconds> temp {duration_cast<seconds>(sys_t() - floor<days>(sys_t()))};
        return temp;
    }
    year_month_day get_current_date() const {return current_date;}
    year get_year() const {return current_date.year();}
    month get_month() const {return current_date.month();}
    weekday get_weekday() const {return current_weekday;}
    day get_day() const {return current_date.day();}
    Date get_date() const {return *this;}
};
bool operator == (const Date& left, const Date& right)
{
    return left.get_current_date() == right.get_current_date();
}
#endif