install.packages("tidyverse")

library(tidyverse)


rainfall <- read_csv('https://tinyurl.com/Oz-fire-rain')

temp <- read_csv('https://tinyurl.com/Oz-fire-temp')

yearly_temp <- read_csv('https://tinyurl.com/Oz-mean-temp')


#filter for max temps from raw temp data
max_temp = filter(temp, temp_type == "max")
#get data from PERTH AIRPORT
perth_max_temp=filter(max_temp, site_name == "PERTH AIRPORT")

split_Column = separate(data = perth_max_temp, col = date, into = c("year", "month", "day"), sep = "-")

#pipes
max_temp %>% filter(site_name =="PERTH AIRPORT") %>%
separate(col=date, into = c("year", "month", "day"), sep = "-") -> store
#End pipe

aggregated_temp = aggregate(temperature~year, store, FUN=mean)

library(lubridate)

temp %>%
  filter(temp_type == "max") %>%
  filter(site_name == "PERTH AIRPORT") %>%
  mutate(year = year(date)) %>%
  filter(year == 2019) %>%
  pull(temperature) %>%
  mean()

'Get the mean of PERTH AIRPORT max temperatures of each year.'

max_temp$year <- year(max_temp$date)
mean_max_temp <- max_temp %>% 
  filter(!is.na(temperature))%>%
  group_by(site_name, year) %>%
  summarize(mean_max_temp = mean(temperature)) #generate a summary table


#Reorder the colors fct_reorder2
mean_max_temp_plot <- ggplot(data = mean_max_temp, aes(year, mean_max_temp, color = site_name)) +
  labs(title = "Temperatures per Year by City", x = "Year", y = "Mean Temperature (Celsius)", color = "") + geom_line() +
  theme_minimal()


cities_label_order <- mean_max_temp %>%
  filter(year == 2019) %>%
  arrange(desc(mean_max_temp)) %>%
  pull(site_name)


temps_across_cities <- read_csv("https://tinyurl.com/Oz-temp-across-cities")

temps_long <- pivot_longer(temps_across_cities,
             "PERTH AIRPORT" : "MELBOURNE (OLYMPIC PARK)",
             names_to = "site",
             values_to = "temp")

rain_across_cities <- read_csv("https://tinyurl.com/Oz-rain-across-cities", guess_max = 10000)

rain_long = pivot_longer(rain_across_cities,
                         "Subiaco Wastewater Treatment Plant": "Melbourne Botanical Gardens",
                         names_to = "site",
                         values_to = "rain")

rain_wide <- pivot_wider(rain_long, 
                        names_from = site, 
                        values_from = rain)

'write_csv(rain_wide, path = "test.csv")'


rainfall_long <-pivot_wider(rainfall,
                            c(year,month,day),
                             values_from = rainfall,
                             names_from = station_name)

#what if we want a wide dataset with total rain for the year

rainfall %>%
  filter(!is.na(rainfall)) %>% pivot_wider(year,
              names_from = station_name,
              values_from = rainfall,
              values_fn = list(rainfall = sum)) -> test


rain_across_stations <- read_csv("https://tinyurl.com/Oz-rain-across-stations",
                                 guess_max = 10000)

station_long<- rain_across_stations %>%
  pivot_longer(4:10,
               names_to = c("city", "station_number"),
               names_pattern = "(.*)_(.*)",
               values_to = "rainfall"
               )

#How has temperature increased over time in Canberra?

temp %>%
  filter(city_name == "CANBERRA") %>%
  filter(temp_type == "max") %>%
  filter(!is.na(temperature)) %>%
  mutate(year = year(date), month = month(date)) %>%
  group_by(month,year)%>%
  summarize(avg_max_temp = mean(temperature)) %>%
  pivot_wider(names_from = month, values_from = avg_max_temp) %>%
  ggplot(aes(month, avg_max_temp, group = year, color = "")) + geom_line()

month_temp_by_period <- temp %>%
  filter(temp_type == "max") %>%
  filter(!is.na(temperature)) %>%
  mutate(month = month(date), year = year(date)) %>%
  #create a new column specifying "early" or "recent"
  mutate(time_period = ifelse(year < 1964, 0, 1))  %>%
  #summary table of avg max temp for each time_period-month combo.
  group_by(time_period, month) %>%
  summarize(avg_max_temp =  mean(temperature))

  ggplot(month_temp_by_period, aes(x = month(month, label = T), y = avg_max_temp, group = factor(time_period), color = factor(time_period))) + geom_line() + 
    labs(title = "Maximum temperature") + xlab("Month") + ylab("Average Max Temperature (C)")+
    scale_color_discrete(name = "", labels = c("Before 1964", "1964 and Later"))
#can also make the y axis be 0 - 30 by using command '+ ylim(0,30)'
  
  ggsave('avg_max_temps.png', width = 6, height = 6)

  #Challenge: repeat analysis above but with data separated for cities in summary table.
  month_temp_by_period_city <- temp %>%
    filter(temp_type == "max") %>%
    filter(!is.na(temperature)) %>%
    mutate(month = month(date), year = year(date)) %>%
    #create a new column specifying "early" or "recent"
    mutate(time_period = ifelse(year < 1964, 0, 1))  %>%
    #summary table of avg max temp for each time_period-month combo.
    group_by(time_period, month, city_name) %>%
    summarize(avg_max_temp =  mean(temperature))
                                                                                                                                                                  #facet_wrap adds a new dimension, splitting the graph into graph per each city.
  ggplot(month_temp_by_period_city, aes(x = month(month, label = T), y = avg_max_temp, group = factor(time_period), color = factor(time_period))) + geom_line() + facet_wrap(~city_name)+
    labs(title = "Maximum temperature") + xlab("Month") + ylab("Average Max Temperature (C)")+
    scale_color_discrete(name = "", labels = c("Before 1964", "1964 and Later"))
  #can also make the y axis be 0 - 30 by using command '+ ylim(0,30)'

  ggsave('avg_max_temps_per_city.png', width = 6, height = 6)

  #How would you compare rainfall and temperature?
  #Need data into single dataframe  
  
  unique(temp$city_name)
  unique(rainfall$city_name)  

  temp <- temp %>%
    mutate(city = recode(city_name, 
           PERTH = "Perth",
           PORT = "NA",
           KENT = "Adelaide",
           BRISBANE = "Brisbane",
           SYDNEY = "Sydney",
           CANBERRA = "Canberra",
           MELBOURNE = "Melbourne"
           )
    ) 
  #Challenge Make the datasets have shared date column(s)
 rain2 <-  rainfall %>%
    mutate(date = ymd(paste(year,month,day, sep="-")))
    
 
 rain_plus_temp <- rain2 %>% filter(!is.na(rainfall)) %>%
   select(city_name, rainfall, date) %>%
   left_join(select(temp, -city_name,-site_name), by = c("date", c("city_name" = "city")))
  
 ggplot(rain_plus_temp, aes(temperature, rainfall, color = temp_type)) + facet_wrap(~city_name) + geom_point()
 
 ggsave('rainfall_temp_by_temp_type_per_city.png', width = 6, height = 6)

 
 rain_plus_temp <- mutate(rain_plus_temp, month = month(date),
                          season = case_when(month > 2 & month < 6~ "fall",
                                             month > 5 & month < 9 ~ "winter",
                                             month > 8 & month < 12 ~ "spring",
                                             month == 12 | month < 3 ~ "summer"))
 
 ggplot(rain_plus_temp,aes(temperature,rainfall)) +
   geom_point() + facet_wrap(~season)
  

 ## Functions
 #Located in file conversion_functions.R
 source('conversion_functions.R')
 
 
 
 FtoC(212)
 

 
rain_plus_temp %>% mutate(tempF = CtoF(temperature),
                           rain_inches = mm_to_inches(rainfall))






#What I missed -----------------------------------------------------------------------

monthly_temps <- temp %>%
  filter(!is.na(temperature)) %>%
  mutate(year = year(date), month = month(date)) %>%
  group_by(month, year) %>%
  summarize(avg_temp = mean(temperature)) 


monthly_temps  %>%
  ggplot(aes(year, avg_temp, color = factor(month))) + 
  geom_point() + geom_smooth(method = "lm", se = FALSE) 

#Get Some stats
monthly_temps %>% 
  lm(avg_temp ~ year, data = .) %>% summary() 
  
#Correlation of All data
monthly_temps  %>%
  ggplot(aes(year, avg_temp)) + 
  geom_point() + geom_smooth(method = "lm", se = FALSE) 

 
#Correlation of just january 
monthly_temps %>% filter(month == 1) %>%
  ggplot(aes(year, avg_temp)) + geom_point() + geom_smooth(method = "lm", se = FALSE)
  

model_Jan <- monthly_temps %>% filter(month == 1) %>%
  lm(avg_temp ~ year, data = .) %>% summary() 


model_Jan %>% broom::tidy()

model_Jan$r.squared

models_changing_temp <- monthly_temps %>%
  split(.$month) %>%
  map(~lm(avg_temp ~ year, data = .)) %>%
  map(summary)

#Vector
models_changing_temp %>% 
  map_dbl("r.squared")

#Dataframe
models_changing_temp %>% 
  map_dfr("r.squared")


library(broom)
models_changing_temp[[1]] %>% 
  tidy()  


#THESE 2 DO THE SAME THING. Maps the Tidy function to the entire dtf.-------------------------
models_changing_temp %>% 
  map_dfr(tidy, .id = 'month') #This one just adds which month each lm relates to.


models_changing_temp %>% 
  map_dfr(tidy)
#--------------------------------------------------------------------------------------------

models_changing_temp %>% 
  map_dfr(tidy, .id = 'month') %>%
  filter(term == 'year') %>% 
  select(-term) %>%
  mutate(r_squared = map_dbl(models_changing_temp,"r.squared"))
#To make a new column we need a vector, so we use map_dbl

#use MUTATE to add a column, in this case we add "r_squared"




#######  Removing Redundant data and put into database #########
colnames(rainfall)

support_table <- rainfall %>%
  select("station_code", "city_name", "lat", "long", "station_name") %>%
  distinct() 

View(support_table)

rainfall_removed_redund <- rainfall %>%
  select(-city_name, -lat, -long,-station_name)



#Get data back with Left Joins and stuff.




