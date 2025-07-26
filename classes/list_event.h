#ifndef list_event_h
#define list_event_h
#include "calendar.h"
#include "event.h"
class list_event 
{
private:
    map<year, map<month, map<day, vector<Event>>>> all_event;
public:
    list_event() = default;
    void add_event(const Event& event) 
    {
        auto& temp_all_event = all_event[event.get_year()][event.get_month()][event.get_day()];
        temp_all_event.push_back(event);
        sort(temp_all_event.begin(), temp_all_event.end(), [](Event& first, Event& second){return first < second;});
    }
    void delete_event(const Event& event) {
        auto& day_events = all_event[event.get_year()][event.get_month()][event.get_day()];
        for (auto it = day_events.begin(); it != day_events.end(); ++it) //iterate through all events for the day
        {
            if (*it == event) 
            {
                day_events.erase(it);
                break;
            }
        }
    }
    template <typename obj>
    void edit_event(Event& event, obj& edit)
    {
        delete_event(event);
        add_event(event.edit(edit));
    }
    bool check_events_day(year_month_day& date) const
    {
        const auto& year_it = all_event.find(date.year()); 
        if (year_it == all_event.end()) 
        {
            cout << "No events for this day\n";
            return false;
        }
        const auto& month_it = year_it->second.find(date.month());
        if (month_it == year_it->second.end()) 
        {
            cout << "No events for this day\n";
            return false;
        }
        const auto& day_it = month_it->second.find(date.day()); 
        if (day_it == month_it->second.end()) 
        {
            cout << "No events for this day\n";
            return false;
        }
        return true;
    }
    void print_events_day(year_month_day date) const
    {
        if(!check_events_day(date))
            return;
        const auto& events = all_event.at(date.year()).at(date.month()).at(date.day());
        if (events.empty()) 
        {
            cout << "No events for this day\n";
            return;
        }
        cout << "Events for " << date.day() << " " << date.month() << " " << date.year() << ":\n";
        cout << "--------------------\n";
        for (const auto& event : events) 
            event.print();
    }
    void print_events_weekday(year_month_day date) const
    {
        const auto& year_it = all_event.find(date.year()); 
        if (year_it == all_event.end()) 
        {
            cout << "No events for this week\n";
            return;
        }
        const auto& month_it = year_it->second.find(date.month());
        if (month_it == year_it->second.end()) 
        {
            cout << "No events for this week\n";
            return;
        }
        weekday tweekday = weekday(date);
        int diff_with_mon = tweekday.c_encoding() != 0 ? tweekday.c_encoding() - 1 : 6; //difference from Monday
        day day_with_mon = date.day() - days{diff_with_mon}; //start from Monday
        vector <vector<Event>> weekday_event;
        for(int i = 0; i != 7; ++i)
        {
            if(all_event.at(date.year()).at(date.month()).find(day_with_mon) !=
                all_event.at(date.year()).at(date.month()).end()) 
                weekday_event.push_back(all_event.at(date.year()).at(date.month()).at(day_with_mon));
            day_with_mon += days{1};
        }
        if (weekday_event.empty()) 
        {
            cout << "No events for this week\n";
            return;
        }
        cout << "Events for week " << (unsigned{day_with_mon} % 7 + unsigned{day_with_mon}) / 7 << " of " << date.month() << " " << date.year() << ":\n";
        cout << "--------------------\n";
        for(const auto& list_events : weekday_event) 
            for(const auto& event : list_events)
                event.print();
    }
    void print_events_month(year_month_day date) const
    {
        const auto& year_it = all_event.find(date.year()); 
        if (year_it == all_event.end()) 
        {
            cout << "No events for this month\n";
            return;
        }
        const auto& month_it = year_it->second.find(date.month());
        if (month_it == year_it->second.end()) 
        {
            cout << "No events for this month\n";
            return;
        }
        auto& events = all_event.at(date.year()).at(date.month());
        cout << "Events for " << date.month() << " " << date.year() << ":\n";
        cout << "--------------------\n";
        for(const auto& [day, month_event] : events)
            for(const auto& day_event : month_event)
                day_event.print();
    }
    void print_events_year(year_month_day date) const
    {
        const auto& year_it = all_event.find(date.year()); 
        if (year_it == all_event.end()) 
        {
            cout << "No events for this year\n";
            return;
        }
        auto& events = all_event.at(date.year());
        cout << "Events for year " << date.year() << ":\n";
        cout << "--------------------\n";
        for (const auto& [month, day_event] : events) 
            for (const auto& [day, list_events] : day_event) 
                for(const auto& event : list_events)
                    event.print();
    }
    vector<Event>& get_vector(year_month_day& date) 
    {
        return all_event.at(date.year()).at(date.month()).at(date.day());
    }
    bool empty() const {return all_event.empty();}
    map<year, map<month, map<day, vector<Event>>>>& get_all_events() {return all_event;}
    ~list_event() {cout << "All events have been deleted!\n";}
};
#endif