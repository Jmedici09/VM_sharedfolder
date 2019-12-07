/*
Name: James Medici
Date: 11/3/19

Description:
Driver for watchdog. Restarts program if watchdog is not feed.
*/

#ifndef COPWDT_H
#define COPWDT_H

void initialize_copwdt();
void feed_the_watchdog();

#endif
