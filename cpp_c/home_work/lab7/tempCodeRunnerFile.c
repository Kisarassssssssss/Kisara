intf("--------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-5d %-20s %-15d %-12s %-12s\n",
               i + 1,
               rec[i].name,
               rec[i].ms,
               rec[i].date,
               rec[i].time_str);
    }
}