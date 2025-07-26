#ifndef event_h
#define event_h
#include "date.h"
class Event 
{
private:
    string name;
    year_month_day date;
    hh_mm_ss<seconds> time;
    int priority;
public:
    Event(const string& tname, const year_month_day& tdate,  const hh_mm_ss<seconds>& ttime, int& tpriority)
    {name = tname; date = tdate; time = ttime; priority = tpriority;}
    year get_year() const {return date.year();}
    month get_month() const {return date.month();}
    day get_day() const {return date.day();}
    hh_mm_ss<seconds> get_time() const {return time;}
    string get_name() const {return name;}
    int get_priority() const {return priority;}
    year_month_day get_date() const {return date;}
    Event& edit(string& edit)
    {
        name = edit;
        return *this;
    }
    Event& edit(year_month_day& edit)
    {
        date = edit;
        return *this;
    }
    Event& edit(hh_mm_ss<seconds>& edit)
    {
        time = edit;
        return *this;
    }
    Event& edit(int& edit)
    {
        priority = edit;
        return *this;
    }
    void print() const 
    {
        ios_base::fmtflags old_flags = cout.flags();
        char old_fill = cout.fill();
        cout << "Event: " << name;
        if(this->get_date() < Date::sys_date() || this->get_date() == Date::sys_date()
                    && this->get_time().to_duration() < Date::sys_time().to_duration())
            cout << " - Overdue";
        cout << "\nDate: " << date.day() << " " << date.month() << " " << date.year() << "\n"
             << "Time: " << setw(2) << setfill('0') << time.hours().count() << ":"
             << setw(2) << setfill('0') << time.minutes().count() << "\n"
             << "Priority: " << priority << "\n";
        cout << "--------------------\n";
        cout.fill(old_fill);  // Restore original fill character
        cout.flags(old_flags);
    }
    virtual string get_description() const {
        return "Event: " + name;
    }
    virtual ~Event() = default;
    
};
class ImportantEvent : public Event {
public:
    using Event::Event; 
    string get_description() const override {
        return "IMPORTANT! " + Event::get_description();
    }
};
bool operator == (const Event& left, const Event& right)
{
    return left.get_date() == right.get_date() && left.get_time().to_duration() == right.get_time().to_duration() 
    && left.get_name() == right.get_name() && left.get_priority() == right.get_priority();
}
bool operator < (const Event& left, const Event& right)
{
    if(left.get_date() < right.get_date()) //by date
        return true;
    else if(left.get_date() == right.get_date())
    {
        if(left.get_time().to_duration() < right.get_time().to_duration()) //if dates equal then by time
            return true;
        else if(left.get_time().to_duration() == right.get_time().to_duration()) //if times equal then by priority
            return left.get_priority() < right.get_priority();
    }
    return false;
}
#endif