#include <iostream>


static bool Year4(int years){
        return (years % 4 == 0 && (years % 100 != 0 || years % 400 == 0));
} 

class Date{
private:
    int years;
    int months;
    int days;

    void Normalize(){

     int days_m[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 0 для индексов месяцев
        
      if(months != 12){
          years += months / 12;
          months %= 12;
        }

      if(months < 0){
          months = 12 + months;
          years -= 1;
        }
        
      if(months == 2 && Year4(years)){
          days_m[2] = 29;
        } 
              
      while(days > days_m[months]){
        days -= days_m[months];
        months += 1;

        if (months > 12){
            years += months/12;
            months %= 12;
        }
    }

      while(days <= 0){
        months -= 1;

        if (months < 1) {
            months = 12;
            years -= 1;
        }
        
        days += days_m[months];
    }
};
    

public:
    Date(int y, int m, int d);
    Date(int d) : Date(0, 0, d){
    
  }
  
    int GetYears() const;
    int GetMonths() const;
    int GetDays() const;
  
    Date& operator += (int d){
        days += d;
        Normalize();
        return *this;
    }
    
    Date operator+ (int d)const{
    int days_pm = days + d;
        return Date(years, months, days_pm);
    }
    
    Date operator- (int d)const{
    int days_pm = days - d;
        return Date(years, months, days_pm);
    }

    void AddDays(int d){
        days += d;
        Normalize();
    }
    
    void PrintDate() const {
        std::cout << years << "\n";
        std::cout << months << "\n";
        std::cout << days << "\n";
    }
};

Date::Date(int y, int m, int d){
    years = y;
    months = m;
    days = d;
    Normalize();
}   

std::ostream& operator << (std::ostream& out, const Date& d){
    out << d.GetYears() << " : " << d.GetMonths() << " : " << d.GetDays();
    return out;
}

std::istream& operator >> (std::istream& in, Date& d){
    int ys, ms, ds;
    char c;
    
    in >> ds >> c;
    in >> ms >> c;
    in >> ys;
    
    d = Date(ys, ms, ds);
    return in;
}

int Date::GetYears() const{
    return years;
}

int Date::GetMonths() const{
    return months;
}

int Date::GetDays() const{
    return days;
}


         
int main(){
  Date d(0, 4, 20);
  std::cout << "Date: " << d << "\n";
  
  d.AddDays(-22);
  std::cout << "Next: " << d << "\n";
  
  return 0;
}
