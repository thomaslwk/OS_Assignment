#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/*----------------------------------------------------------
    ========================================================
    Paper (5): Improved RR CPU Scheduling Algorithm
    ========================================================
    Program notes:  
    ========================================================
    ** main() ** 
    -------------
    Description: Program's main method. Will take user input 
    and call 2 functions. 
    1. DisplayTimeQuantum() 
    2. RunSimulation()
    --------------------------------------------------------
    * AT[] = (Int) Array to store arrival time
    * WT[] = (Int) Array to store wait time
    * TAT[] = (Int) Array to store turn around time
    * P_Flag[] = (Bool) Array to store status flag 
    --------------------------------------------------------
    ** RunSimulation() ** 
    -----------------------
    Description: Main Round robin algorithm logic executed 
    here. 
    --------------------------------------------------------
    Variables: 
    ----------
    * Avg_WT = (Float) Var. to cal. avg. wait time 
    * Avg_TT = (Float) Var. to cal. avg. turn around time
    * RQ_ctr = (Int) Var. to keep track of no. of 
               process remaining in ready queue.
    * temp_WT = (Int) Var. to keep track of total 
               time spent executing process. 
    * ctx_s = (Int) Var. to track no. of context switches.
    * exit_t = (Int) Var. to cal. turnaround time 
                formula. 
    * rem_BT[] = (Int) Array to track remaining burst time
    * new_TQ[] = (Int) Array to store new time quantum 
                 for each process base on priority.
    --------------------------------------------------------
    ** DisplayTimeQuantum() **
    --------------------------
    Description: Print default time quantum and new time
    quantum base for each priority level. Will use getter 
    methods to get cal. for each priority level's respective
    time quantum. 
    --------------------------------------------------------
    ** Getter Methods **
    ---------------------
    * GetLowPriority()
        => Return time quantum for low priority.  
    * GetMediumPriority() 
        => Return time quantum for medium priority. 
    * GetHighPriority() 
        => Return time quantum for high priority. 
    ========================================================
    Assumptions: (Value not stated in paper.)
    ========================================================
    * Very Low Burst => Any value greater than 0, less than 
                        101.
-----------------------------------------------------------*/

/*-----------------------------------------------
 Getter methods to return new Time Quantum value 
 base on priority value. 
-------------------------------------------------*/
int GetLowPriority(int n, int TQ) {
    //-- Create variable for low priority. 
    int low_p = 0; 
    low_p = (TQ - (0.2*TQ));
    return low_p;
}
int GetMediumPriority(int n, int TQ) {
    //-- Create variable for medium priority. 
    int medium_p = 0; 
    medium_p = TQ; 
    return medium_p;
}
int GetHighPriority(int n, int TQ) {
    //-- Create variable for high priority. 
    int high_p = 0; 
    high_p = (TQ + (0.2*TQ));
    return high_p;
}

/*-----------------------------------------------
 Function to display new Time Quantum base on 
 process priority value. 
------------------------------------------------*/
int DisplayTimeQuantum(int n, int TQ) {
    //-- Display different Time Quantum base on priority level
    printf("\n------------------------------------\n");
    printf("***** Time Quantum: %d *****\n", TQ);
    printf("------------------------------------");
    printf("\nTime Quantum for High Priority Process: %d", GetHighPriority(n, TQ));
    printf("\nTime Quantum for Medium Priority Process: %d", GetMediumPriority(n, TQ));
    printf("\nTime Quantum for Low Priority Process: %d", GetLowPriority(n, TQ));
    printf("\n------------------------------------\n");
    return 1;
}

/*-------------------------------------------------
 Function to start main simulation flow of improved 
 Round robin scheduler. 
--------------------------------------------------*/
int RunSimulation(int n, int TQ, int BT[], int AT[], int WT[], 
    int TAT[], int P_val[], bool P_flag[]) {
    //-- Create temp variables for calculation. 
    int RQ_ctr = 0, temp_WT = 0, exit_t = 0, ctx_s = 0, rem_RQ = 0, rem_BT[n], new_TQ[n];
    memset(rem_BT, 0, n*sizeof(int));
    memset(new_TQ, 0, n*sizeof(int));
    //-- Push all process into ready queue. 
    RQ_ctr = n;
    //-- Initialise variables for avg calculation. 
    float Avg_WT = 0.0, Avg_TT = 0.0;

    //-- Create duplicate array of BT[i] for remainder BT cal.
    //-- Calculate each process's new time quantum. 
    for(int i = 0; i < n; i++){
        rem_BT[i] = BT[i];
        //-- If low priority. 
        if(P_val[i] == 1){
            new_TQ[i] = GetLowPriority(n, TQ);
        }
        //-- If medium priority.
        else if(P_val[i] == 2){
            new_TQ[i] = GetMediumPriority(n, TQ);
        }
        //-- If high priority. 
        else if(P_val[i] == 3){
            new_TQ[i] = GetHighPriority(n, TQ);
        }
    }
    
    //-- Main loop to execute Paper's Improved simulation.
    printf("\n------------------------------------\n");
    printf("***** Paper (5) RR Simulation *****\n");
    printf("------------------------------------\n");
    printf("***** Gantt Chart *****\n");
    printf("------------------------------------\n");
    
    while(1){
        //-- Set default process status to true. No process running. 
        bool process_status = true;
        for(int i = 0; i < n; i++){
            /*-----------------------------------
             Cond: Check for Low BT. (Assumption) 
             Assumption: Low BT is 1 to 100. 
            -------------------------------------*/ 
            if(rem_BT[i] > 0 && rem_BT[i] <= 100){           
                /*------------------------
                 When process is executed: 
                 * Set Process flag to true
                -------------------------*/
                P_flag[i] = 1;

                //-- Calculate turnaround time. 
                //exit time => temp time + burst time (execute time)
                //tat = exit time - arrival time
                exit_t = temp_WT + rem_BT[i];
                TAT[i] = exit_t - AT[i];

                //-- Calculate Wait time. 
                //wT = turnaround time - burst time 
                WT[i] = TAT[i] - BT[i];

                //-- Add computing time to temp time.
                //temp time = temp time + time used by process.  
                temp_WT += rem_BT[i];

                //-- Print for Gantt Chart
                printf("%d (%d)| ", i+1, temp_WT);
                //-- Add count to context switch ctr.
                ctx_s++;

                /*-------------------------------
                 When task is complete: 
                 * Set remaining burst time to 0. 
                 * Set exit time to 0.
                 * Remove from ready queue.  
                 * Set process status to false.
                --------------------------------*/ 
                //-- When task is complete, set the remaining burst time to 0. 
                rem_BT[i] = 0; 
                //-- When task is complete, set exit time to 0.
                exit_t = 0;
                RQ_ctr--;
                //-- Set process status to false. Pending task.
                process_status = false;    
                //-- Print calculation. 
                // printf("\n\t%d\t%d\t\t%d\t\t%d",i+1, BT[i], WT[i], TAT[i]); 
            }
        }
        for(int i = 0; i < n; i++){
            /*------------------------------------------------------
             * Cond: If not low BT, begin check for other condition. 
            -------------------------------------------------------*/ 
            if(rem_BT[i] > 100){
                /*-------------------------------------------
                 * Cond: If true, execute entire process for 
                 it's remaining burst time. (Paper: cond - 8)
                --------------------------------------------*/
                if(rem_BT[i] <= new_TQ[i]){
                    /*------------------------
                     When process is executed: 
                     * Set Process flag to true
                    -------------------------*/
                    P_flag[i] = 1;

                    //-- Calculate turnaround time. 
                    //exit time => temp time + burst time (execute time)
                    //tat = exit time - arrival time
                    exit_t = temp_WT + rem_BT[i];
                    TAT[i] = exit_t - AT[i];

                    //-- Calculate Wait time. 
                    //wT = turnaround time - burst time 
                    WT[i] = TAT[i] - BT[i];

                    //-- Add computing time to temp time.
                    //temp time = temp time + time used by process.  
                    temp_WT += rem_BT[i];

                    //-- Print for Gantt Chart
                    printf("%d (%d)| ", i+1, temp_WT);
                    //-- Add count to context switch ctr.
                    ctx_s++;

                    /*-------------------------------
                     When task is complete: 
                     * Set remaining burst time to 0. 
                     * Set exit time to 0.
                     * Remove from ready queue.  
                     * Set process status to false.
                    --------------------------------*/ 
                    //-- When task is complete, set the remaining burst time to 0. 
                    rem_BT[i] = 0;
                    //-- When task is complete, set exit time to 0.
                    exit_t = 0;
                    //-- When task is complete, remove from ready queue. 
                    RQ_ctr--;
                    //-- Set process status to false. Pending task.
                    process_status = false;    
                    //-- Print calculation. 
                    // printf("\n\t%d\t%d\t\t%d\t\t%d",i+1, BT[i], WT[i], TAT[i]); 
                }
                /*-------------------------------------------
                 * Cond: If true, execute entire process for 
                 it's remaining burst time. (Paper: cond - 9)
                --------------------------------------------*/ 
                else if((rem_BT[i] > new_TQ[i]) && rem_BT[i] <= (new_TQ[i] + (0.3 * new_TQ[i])) && P_val[i] == 3){    
                    /*------------------------
                     When process is executed: 
                     * Set Process flag to true
                    -------------------------*/
                    P_flag[i] = 1;

                    //-- Calculate turnaround time. 
                    //exit time => temp time + burst time (execute time)
                    //tat = exit time - arrival time
                    exit_t = temp_WT + rem_BT[i];
                    TAT[i] = exit_t - AT[i];

                    //-- Calculate Wait time. 
                    //wT = turnaround time - burst time 
                    WT[i] = TAT[i] - BT[i];

                    //-- Add computing time to temp time.
                    //temp time = temp time + time used by process.  
                    temp_WT += rem_BT[i];

                    //-- Print for Gantt Chart
                    printf("%d (%d)| ", i+1, temp_WT);
                    //-- Add count to context switch ctr.
                    ctx_s++;

                    /*-------------------------------
                     When task is complete: 
                     * Set remaining burst time to 0. 
                     * Set exit time to 0.
                     * Remove from ready queue.  
                     * Set process status to false.
                    --------------------------------*/ 
                    //-- When task is complete, set the remaining burst time to 0. 
                    rem_BT[i] = 0; 
                    //-- When task is complete, set exit time to 0.
                    exit_t = 0;
                    //-- When task is complete, remove from ready queue. 
                    RQ_ctr--;
                    //-- Set process status to false. Pending task.
                    process_status = false;    
                    //-- Print calculation. 
                    // printf("\n\t%d\t%d\t\t%d\t\t%d",i+1, BT[i], WT[i], TAT[i]); 
                }
                /*-------------------------------------------
                 * Cond: If true, execute entire process for 
                 it's remaining burst time. (Paper: cond - 10)
                --------------------------------------------*/ 
                else if((rem_BT[i] > new_TQ[i]) && rem_BT[i] <= (new_TQ[i] + (0.2 * new_TQ[i])) && (P_val[i] == 2 || P_val[i] == 1)){
                    /*------------------------
                     When process is executed: 
                     * Set Process flag to true
                    -------------------------*/
                    P_flag[i] = 1;

                    //-- Calculate turnaround time. 
                    //exit time => temp time + burst time (execute time)
                    //tat = exit time - arrival time
                    exit_t = temp_WT + rem_BT[i];
                    TAT[i] = exit_t - AT[i];

                    //-- Calculate Wait time. 
                    //wT = turnaround time - burst time 
                    WT[i] = TAT[i] - BT[i];

                    //-- Add computing time to temp time.
                    //temp time = temp time + time used by process.  
                    temp_WT = temp_WT + rem_BT[i];

                    //-- Print for Gantt Chart
                    printf("%d (%d)| ", i+1, temp_WT);
                    //-- Add count to context switch ctr.
                    ctx_s++;

                    /*-------------------------------
                     When task is complete: 
                     * Set remaining burst time to 0. 
                     * Set exit time to 0.
                     * Remove from ready queue.  
                     * Set process status to false.
                    --------------------------------*/ 
                    //-- When task is complete, set the remaining burst time to 0. 
                    rem_BT[i] = 0;
                    //-- When task is complete, set exit time to 0.
                    exit_t = 0;
                    //-- When task is complete, remove from ready queue. 
                    RQ_ctr--;
                    //-- Set process status to false. Pending task.
                    process_status = false;    
                    //-- Print calculation. 
                    // printf("\n\t%d\t%d\t\t%d\t\t%d",i+1, BT[i], WT[i], TAT[i]); 
                }
                /*----------------------------------
                 Execute the remaining process that 
                 did not meet any special condition. 
                -----------------------------------*/ 
                else{ 
                    //-- If Priority is low.
                    if(P_val[i] == 1){
                        //-- Set process status to false. Pending task.
                        process_status = false;        
                        //-- Subtract time quantum for low priority from remainder burst time. 
                        rem_BT[i] -= new_TQ[i];
                        //-- Add computing time to temp time.
                        //temp time = temp time + time used by process.  
                        temp_WT += new_TQ[i];
                        //-- Print for Gantt Chart
                        printf("%d (%d)| ", i+1, temp_WT);
                        //-- Add count to context switch ctr.
                        ctx_s++;
                    }
                    //-- If Priority is medium. 
                    else if(P_val[i] == 2){
                        //-- Set process status to false. Pending task.
                        process_status = false;     
                        //-- Subtract time quantum for medium priority from remainder burst time. 
                        rem_BT[i] -= new_TQ[i];
                        //-- Add computing time to temp time.
                        //temp time = temp time + time used by process.  
                        temp_WT += new_TQ[i];     
                        //-- Print for Gantt Chart
                        printf("%d (%d)| ", i+1, temp_WT);
                        //-- Add count to context switch ctr.
                        ctx_s++;
                    }
                    //-- If Priority is high. 
                    else if(P_val[i] == 3){
                        //-- Set process status to false. Pending task.
                        process_status = false;     
                        //-- Subtract time quantum for high priority from remainder burst time. 
                        rem_BT[i] -= new_TQ[i];
                        //-- Add computing time to temp time.
                        //temp time = temp time + time used by process.  
                        temp_WT += new_TQ[i];
                        //-- Print for Gantt Chart
                        printf("%d (%d)| ", i+1, temp_WT);
                        //-- Add count to context switch ctr.
                        ctx_s++;
                    }
                }
            }
        }
        /*-------------------------------------
         If no process running and no. of 
         processes in ready queue is 0,
         end while loop.
         --------------------------------------*/ 
        if(process_status == true && RQ_ctr == 0){
            break;
        }
    }
    /*------------------------------------------
     Function to calculate Average Wait time and 
     Average Turnaround time. Print output. 
    --------------------------------------------*/
    printf("\n------------------------------------\n");
    printf("***** Process Table *****\n");
    printf("------------------------------------\n");
    //-- Print table header.
    printf("Process \tBurst Time \tArrival Time \tWaiting Time \tTurn Around Time"); 
    for(int i = 0; i < n; i++){
        //-- Calculate Total Avg_WT and Avg_TT 
        Avg_WT += WT[i];
        Avg_TT += TAT[i];
        //-- Print output. 
        printf("\n\t%d\t%d\t\t%d\t\t%d\t\t%d",i+1, BT[i], AT[i], WT[i], TAT[i]); 
    }
    //-- Print Average Wait time and Average Turn around time. 
    printf("\n------------------------------------\n");
    printf("\nAverage Waiting Time: %0.1f", Avg_WT/n);
    printf("\nAverage Turnaround Time: %0.1f", Avg_TT/n);
    printf("\nTotal no. of context switches: %d\n", ctx_s);
    return 1;
}


/*------------
 Main Function 
-------------*/ 
int main()
{
    /*--------------------------------
     Intialise variables used in main. 
     ---------------------------------*/
    //-- Variables to store new TQ based on priority. 
    int n = 0, TQ = 0;

    /*--------------------------------------------
     1. Input no. of Process and define essential 
     variables. 
     --------------------------------------------*/
    printf("------------------------------------\n");
    printf("***** Start of Program *****\n");
    printf("------------------------------------\n");
    printf("Enter the no. of processes: ");
    //-- Scan usr input for no. of process input.
    scanf("%d", &n);  

    /*----------------------------
     Intialise arrays to be used. 
    -----------------------------*/
    int BT[n], AT[n], PID[n], P_val[n];
    int TAT[n], WT[n], Pid[n];
    bool P_flag[n];

    //-- Set all values in array to 0. (Normal Array)
    memset(BT, 0, n*sizeof(int));
    memset(AT, 0, n*sizeof(int));
    memset(WT, 0, n*sizeof(int));
    memset(PID, 0, n*sizeof(int));
    memset(TAT, 0, n*sizeof(int));
    memset(P_val, 0, n*sizeof(int));
    
    //-- Set default flag to false. (Bool Array)
    memset(P_flag, 0, n*sizeof(int));

    /*----------------------------------------------
     Set Time quantum for algorithm based on user
     input. 
    ----------------------------------------------*/
    // printf("Enter a Time Quantum for process:");
    //-- Scan user input for Time quantum
    scanf("%d", &TQ);

    /*--------------------------------------------------
     3. Loop to take user input for process and 
     priority level for each process. 
    ----------------------------------------------------*/ 
    for(int i = 0; i < n; i++){
        // printf("\n------------------------------------\n");
        // printf("*** PRIORITY INPUT: %d ***\n", i+1);
        // printf("------------------------------------");
        // //-- Allow user input for Burst time. 
        // printf("\nEnter Burst Time(BT) for process %d: ", i+1);
        //-- Scan user input for burst time
        scanf("%d", &BT[i]);

        //-- Allow user input for Arrival time. 
        // printf("\nEnter Arrival Time(BT) for process %d: ", i+1);
        //-- Scan user input for arrival time. 
        scanf("%d", &AT[i]);

        //-- Allow user input for Priority level.
        // printf("\nEnter Priority Value: (1-3) for process %d: ", i+1);
        //-- Scan user input for priority level.
        scanf("%d", &P_val[i]);
        //-- Validate Priority value input. 
        if(P_val[i] < 1 || P_val[i] > 3) {
            printf("\n------------------------------------\n");
            printf("Enter a value from (1-3).");
            return 0;
        }
    }
    printf("\n------------------------------------\n");
    //-- Sort by arrival time. 
    // for(int i = 0; i < n; i++) {
    //     int pos = i, tempx;
    //     for(int j = i; j < n; j++){
    //         if(AT[j] < AT[pos]){
    //             pos = j; 
    //         }
    //     }
    //     PID[i] = i;
    //     tempx = AT[i];
    //     AT[i] = AT[pos];
    //     AT[pos] = tempx;

    //     tempx = BT[i];
    //     BT[i] = BT[pos];
    //     BT[pos] = tempx;
        
    //     tempx = P_val[i];
    //     P_val[i] = P_val[pos];  
    //     P_val[pos] = tempx;
    // }

    /*-------------------------------------------
     Function to display new time quantum values. 
    --------------------------------------------*/
    DisplayTimeQuantum(n, TQ);
    /*----------------------------------------
     Function to start Round robin simulation. 
    -----------------------------------------*/
    RunSimulation(n, TQ, BT, AT, WT, TAT, P_val, P_flag);
    return 0;
}
