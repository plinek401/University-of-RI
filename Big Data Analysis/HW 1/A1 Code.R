#Pawel Linek
#HW 1

#install.packages("tidyverse")
#install.packages("gapminder")
#install.packages("directlabels")
library(tidyverse)
library(gapminder)
library(directlabels)

data <- read_csv("https://tinyurl.com/student-teacher")

#gapminder
#data

#colnames(gapminder)
#colnames(data)

#Cuts down gapminder to only include rows where the year is the maximum value (2007) to look at more recent data.
gapminder_modernish <- gapminder[gapminder$year>2006,]  

  
#Merge dataframes into 1 dataframe
temp <- merge(data, gapminder_modernish, by="country")

#Perform a few column drops.
data_dropped <-select(temp, -c("flag_codes", "flags", "edulit_ind", "year.y"))

#We get our dataframe We're going to work with, With all relevant data.
data_dropped
  
#Using Summarize to show change in mean student ratio over time by continent to compare geographic locations impact on student ratio. (Use in RMarkdown)
mean_ratios <- data_dropped %>%
  filter(!is.na(student_ratio)) %>%
  group_by(year.x, continent) %>%
  summarize(mean_student_ratio = mean(student_ratio)) 

ggplot(mean_ratios, aes(year.x, mean_student_ratio, color=continent)) +
 geom_point() +geom_line() + xlab("Year") + ylab("Mean student ratio") + ggtitle("Mean student ratio over time per continent")

#----------------------------------------------------------------------

#Plots the most and least populous countries in each continent(oceania only has New Zealand as a country so oceania only has 1 plot), and compares The range of the student_ratio between these min and max continent leaders.
range_pop_ratio <- data_dropped %>%
  filter(!is.na(student_ratio)) %>%
  filter(year.x==2012)%>% 
  group_by(country, continent, pop, student_ratio) %>% 
  summarize(mean(student_ratio)) %>%
  group_by(continent) %>%
  filter(pop == max(pop) | pop == min(pop))

labels <- range_pop_ratio %>%
  arrange(continent) %>% pull(country)
  
ggplot(range_pop_ratio, aes(continent, student_ratio, group(continent), color=country, lwd = 2)) +
   geom_line() + theme_bw() + scale_color_discrete(breaks = labels, labels = labels) + xlab("Continent") + ylab("Student Ratio") + ggtitle("Range of student ratio by continent mins and maxs")

#-------------------------------------------------------------------------------------------

#Next We will plot each (min) and (max) countries per continent, student ratio over time
data_dropped %>%
  filter(!is.na(student_ratio)) %>%
  filter(country == "Ethiopia" | country == "Sao Tome and Principe" | country == "Brazil" | country == "Jamaica" | country == "Bahrain" | country == "China" | country == "Germany"| country == "Iceland" | country == "New Zealand") %>% 
  group_by(country, year.x, continent) %>%
  summarize(mean_student_ratio = mean(student_ratio))  %>% 
  ggplot(aes(year.x, mean_student_ratio, group = country, color=continent)) +
  geom_point() +geom_line() + xlab("Year") + ylab("Mean student ratio") + ggtitle("Mean student ratio over time per min/max country") + 
  geom_dl(aes(label = country), method = list(dl.combine("last.points"), cex = 0.8))  + scale_x_continuous(expand=c(0, 1))

#-----------------------------------------------------------------------------------------

#Compare GDP to Student Ratio.

gdpToRatio <- data_dropped %>%
  filter(!is.na(student_ratio)) %>%
  group_by(country, continent, gdpPercap) %>%
  summarize(avg_ratio = mean(student_ratio, na.rm = T))

ggplot(gdpToRatio, aes(gdpPercap, avg_ratio, 
                                  group=continent)) +
  geom_point() + facet_wrap(~continent) +
  labs(y = "Mean Student Ratio",
       x = "GDP Per Capita") +
  geom_dl(aes(label = country), method = list(cex = .7, hjust = -.1))  + scale_x_continuous(expand=c(.1, 1)) + geom_smooth(method = "lm", se = FALSE) 

