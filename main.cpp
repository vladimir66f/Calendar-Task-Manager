#include "work_with_txt/txt.h"
#include "classes/list_event.h"
bool error()
{
    if (cin.fail()) 
    {
        cin.clear(); // Reset stream state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        cout << "Invalid input!\n";
        return true;
    }
    return false;
}
bool error(int left, int right, unsigned cmd)
{
    if (cin.fail() || left > cmd || right < cmd) 
    {
        cin.clear(); // Reset stream state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        cout << "Invalid input!\n";
        return true;
    }
    return false;
}
bool error_date(int tyear, unsigned tmonth, unsigned tday)
{
    if(tday < 1 || tday > 31)
    {
        cout << "Invalid date!\n";
        return true;
    }
    if(tmonth < 1 || tmonth > 12)
    {
        cout << "Invalid date!\n";
        return true;
    }
    if(tyear < 0)
    {
        cout << "Invalid date!\n";
        return true;
    }
    year_month_day date{year{tyear}, month{tmonth}, day{tday}};
    if (!date.ok()) 
    {
        cout << "Invalid date!\n";
        return true;
    }
    return false;
}
int main()
{
    list_event all_events; 
    Calendar calendar;
    readEventsFromTxt(all_events);
    setlocale(LC_ALL, "rus");
    while(true)
    {
        unsigned cmd;
        cout << "\n\nCalendar - Task Manager\n1 - View events\n2 - View calendar\n" 
             << "3 - Add event\n4 - Edit event\n5 - Delete event\n6 - Exit program\n\n\n";
        cin >> cmd;
        if(error(1, 6, cmd))
            continue;
        calendar.update_time();
        if(cmd == 1) //1 - View events
        {
            cout <<"\n\n1 - View today's events\n2 - View this week's events\n" 
                 << "3 - View this month's events\n4 - View this year's events\n5 - View events for another date\n\n\n";
            cin >> cmd;
            if(error(1, 5, cmd))
                continue;
            cout << "\n\n";
            switch (cmd)
            {
                case 1: all_events.print_events_day(calendar.get_current_date()); break;
                case 2: all_events.print_events_weekday(calendar.get_current_date()); break;
                case 3: all_events.print_events_month(calendar.get_current_date()); break;
                case 4: all_events.print_events_year(calendar.get_current_date()); break;
                case 5: cout << "1 - View events for specific day\n2 - View events for specific week\n" 
                    << "3 - View events for specific month\n4 - View events for specific year\n\n\n";
                    int ev_cmd;
                    cin >> ev_cmd;
                    if(error(1, 4, ev_cmd))
                        continue;
                    if(ev_cmd == 1)
                    {
                        int tyear;
                        unsigned  tmonth, tday;
                        cout << "Enter day in format: 26 04 2006 (day - month - year)\n";
                        year_month_day printday;
                        cin >> tday >> tmonth >> tyear;
                        if(error())
                            break;
                        if(!error_date(tyear, tmonth, tday))
                        {
                            printday = year_month_day{year{tyear}, month{tmonth}, day{tday}};
                            all_events.print_events_day(printday);
                        }
                    }
                    if(ev_cmd == 2)
                    {
                        int tyear;
                        unsigned tmonth, tweek;
                        cout << "Enter week in format: 3 04 2006 (week - month - year)\n";
                        cin >> tweek >> tmonth >> tyear;
                        if(error())
                            break;
                        if(!error_date(tyear, tmonth, 1 + (tweek - 1) * 7))
                        {
                            year_month_day printday{year{tyear}, month{tmonth}, day{1 + (tweek - 1) * 7}};
                            all_events.print_events_weekday(printday);
                        }
                    }
                    if(ev_cmd == 3)
                    {
                        int tyear;
                        unsigned tmonth;
                        cout << "Enter month in format: 04 2006 (month - year)\n";
                        cin >> tmonth >> tyear;
                        if(error())
                            break;
                        if(!error_date(tyear, tmonth, 1))
                        {
                            year_month_day printday{year{tyear}, month{tmonth}, day{1}};
                            all_events.print_events_month(printday);
                        }
                    }
                    if(ev_cmd == 4)
                    {
                        int tyear;
                        cout << "Enter year in format: 2006 (year)\n";
                        cin >> tyear;
                        if(error())
                            break;
                        if(!error_date(tyear, 1, 1))
                        {
                            year_month_day printday{year{tyear}, month{1}, day{1}};
                            all_events.print_events_year(printday);
                        }
                    }
            } 
            continue;
        }
        if(cmd == 2) //2 - View calendar
        {
            cout <<"\n\n1 - View today's calendar\n2 - View this week's calendar\n" 
                 << "3 - View this month's calendar\n4 - View this year's calendar\n5 - View calendar for another date\n\n\n";
            cin >> cmd;
            if(error(1, 5, cmd))
                continue;
            cout << "\n\n";
            switch (cmd)
            {
                case 1: calendar.print_day(calendar.get_current_date()); break;
                case 2: calendar.print_head_week(); calendar.print_week(calendar.get_current_date()); break;
                case 3: calendar.print_month(calendar.get_current_date()); break;
                case 4: calendar.print_year(calendar.get_current_date()); break;
                case 5: cout << "1 - View calendar for specific week\n2 - View calendar for specific month\n"
                             << "3 - View calendar for specific year\n\n\n";
                    int ev_cmd;
                    cin >> ev_cmd;
                    if(error(1, 3, ev_cmd))
                        continue;
                    if(ev_cmd == 1)
                    {
                        int tyear;
                        unsigned tmonth, tweek;
                        cout << "Enter week in format: 3 04 2006 (week - month - year)\n";
                        cin >> tweek >> tmonth >> tyear;
                        if(error())
                            break;
                        if(!error_date(tyear, tmonth, 1 + (tweek - 1) * 7))
                        {
                            year_month_day printday{year{tyear}, month{tmonth}, day{1 + (tweek - 1) * 7}};
                            calendar.print_head_week();
                            calendar.print_week(printday);
                        }
                    }
                    if(ev_cmd == 2)
                    {
                        int tyear;
                        unsigned tmonth;
                        cout << "Enter month in format: 04 2006 (month - year)\n";
                        cin >> tmonth >> tyear;
                        if(error())
                            break;
                        if(!error_date(tyear, tmonth, 1))
                        {
                            year_month_day printday{year{tyear}, month{tmonth}, day{1}};
                            calendar.print_month(printday);
                        }
                    }
                    if(ev_cmd == 3)
                    {
                        int tyear;
                        cout << "Enter year in format: 2006 (year)\n";
                        cin >> tyear;
                        if(error())
                            break;
                        if(!error_date(tyear, 1, 1))
                        {
                            year_month_day printday{year{tyear}, month{1}, day{1}};
                            calendar.print_year(printday);
                        }
                    }
            } 
            continue;
        }
        if(cmd == 3) //3 - Add event
        {
            cout << "Enter event name:\n";
            string name;
            cin >> name;
            cout << "Set event priority:\n1 - High priority\n2 - Medium priority\n3 - Low priority\n4 - No priority\n";
            int priority;
            cin >> priority;
            if(error(1, 4, priority))
                continue;
            int tyear;
            unsigned tmonth, tday;
            cout << "Enter day in format: 26 04 2006 (day - month - year)\n";
            cin >> tday >> tmonth >> tyear;
            if(error() || error_date(tyear, tmonth, tday))
                continue;
            year_month_day event_date{year{tyear}, month{tmonth}, day{tday}};
            cout << "Enter event time in 24-hour format (hours - minutes):\n";
            unsigned hour, minute;
            cin >> hour >> minute;
            if(error())
                continue;
            if(hour > 24 || minute > 59)
            {
                cout << "Invalid time!\n";
                continue;
            }
            auto event_duration = hours{hour} + minutes{minute};
            hh_mm_ss<seconds> event_time{duration_cast<seconds>(event_duration)};
            Event* newEventPtr = nullptr;
            if(priority == 1)
                newEventPtr = new ImportantEvent(name, event_date, event_time, priority);
            else 
                newEventPtr = new Event(name, event_date, event_time, priority);
            cout << "Created: " << newEventPtr->get_description() << "\n";
            all_events.add_event(*newEventPtr);
            delete newEventPtr;
            continue;
        }
        if(cmd == 4) //4 - Edit event
        {
            int tyear;
            unsigned tmonth, tday;
            cout << "Enter day in format: 26 04 2006 (day - month - year)\n";
            cin >> tday >> tmonth >> tyear;
            if(error() || error_date(tyear, tmonth, tday))
                continue;
            year_month_day date{year{tyear}, month{tmonth}, day{tday}};
            if(!all_events.check_events_day(date))
                continue;
            cout << "Select event from list:\n";
            cout << "--------------------\n";
            vector<Event>vector_events = all_events.get_vector(date);
            for(size_t i = 0; i != vector_events.size(); ++i)
            {
                cout << i + 1 << ".\n";
                vector_events[i].print();
            }
            int index = 0;
            cin >> index;
            --index;
            if(error(0, vector_events.size() - 1, index))
                continue; 
            while(cmd != 5)
            {
                cout << "Select parameter to edit:\n1 - Event name\n" 
                 << "2 - Event date\n3 - Event time\n4 - Event priority\n5 - Exit edit mode\n";
                cin >> cmd;
                if(error(1, 5, cmd))
                    continue;
                switch(cmd)
                {
                    case 1:
                    {
                        string tname;
                        cout << "Enter new event name\n";
                        cin >> tname;
                        all_events.edit_event(vector_events[index], tname);
                        break;
                    }
                    case 2:
                    {
                        int tyear;
                        unsigned tmonth, tday;
                        cout << "Enter new day in format: 26 04 2006 (day - month - year)\n";
                        cin >> tday >> tmonth >> tyear;
                        if(error() || error_date(tyear, tmonth, tday))
                            break;
                        date = year_month_day{year{tyear}, month{tmonth}, day{tday}};
                        all_events.edit_event(vector_events[index], date);
                        break;
                    }
                    case 3:
                    {
                        cout << "Enter new event time in 24-hour format (hours - minutes):\n";
                        unsigned hour, minute;
                        cin >> hour >> minute;
                        if(error())
                            break;
                        if(hour > 24 || minute > 59)
                        {
                            cout << "Invalid time!\n";
                            break;
                        }
                        auto event_duration = hours{hour} + minutes{minute};
                        hh_mm_ss time {duration_cast<seconds>(event_duration)};
                        all_events.edit_event(vector_events[index], time);
                        break;
                    }
                    case 4:
                    {
                        int priority;
                        cout << "Set event priority:\n1 - High priority\n2 - Medium priority\n3 - Low priority\n4 - No priority\n";
                        cin >> priority;
                        if(error(1, 4, priority))
                            break;
                        all_events.edit_event(vector_events[index], priority);
                    }
                }
                cout << "Event updated!\n";
            }
            continue;
        }
        if(cmd == 5) //5 - Delete event
        {
            int tyear;
            unsigned tmonth, tday;
            cout << "Enter day in format: 26 04 2006 (day - month - year)\n";
            cin >> tday >> tmonth >> tyear;
            if(error() || error_date(tyear, tmonth, tday))
                break;
            year_month_day date{year{tyear}, month{tmonth}, day{tday}};
            if(!all_events.check_events_day(date))
                continue;
            cout << "Select event from list:\n";
            cout << "--------------------\n";
            vector<Event>& vector_events = all_events.get_vector(date);
            for(size_t i = 0; i != vector_events.size(); ++i)
            {
                cout << i + 1 << ".\n";
                vector_events[i].print();
            }
            int index = 0;
            cin >> index;
            --index;
            if(error(0, vector_events.size() - 1, index))
                continue; 
            all_events.delete_event(vector_events[index]);
            cout << "Event deleted!\n";
        }
        if(cmd == 6) //6 - Exit program
            break;
    }
    saveEventsToTxt(all_events.get_all_events());
}