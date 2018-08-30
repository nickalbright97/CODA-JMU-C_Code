/*
*   V700
 *  6-8 2:15  v107
 * File:
 *    QDC 792 type   .c
 *
 * Description:
 *    Strobe output of specified channel to test control/flipflop input 1.
 *
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jvme.h"
#include "c775Lib.h"
#include <time.h>

// Values from tdcshort.cc
#define TDC0_BASE_ADDR         0x00440000
#define TDC_BASE_INCR          0x010000
#define N_TDC                  1
#define CRATE_ID               0


static UINT16 tdc_id            =0;
static int tdc_status           =0;
static int ndataTDC=0;
static int tdc_no_events;



int 
main()
{
  unsigned int retTime;

    int jj;
    int ii;
    int i;
    int no_MEB;
    
    UINT32 data[34];
    //Buf[15000];
    
  printf("\n  Tst: CAEN 775 test \n");
  printf("Tst: --------open vme window--------------------\n");

  vmeSetQuietFlag(1);
  ii=1;
  no_MEB=1;
  if(vmeOpenDefaultWindows()!=OK)   goto CLOSE;

  /* Initialize the sis3610 */
  // cout << "Initializing V775 TDC units...BASE = "<< TDC0_BASE_ADDR << endl;
    printf("Tst: Initializing V775 TDC units...BASE = %d,  0x%08x \n", TDC0_BASE_ADDR, TDC0_BASE_ADDR);

  if(c775Init(TDC0_BASE_ADDR,TDC_BASE_INCR,1,CRATE_ID)==ERROR){
      printf("Tst: Initializing error");
   goto CLOSE;
  }
 
  printf(" Tst:  init success \n");
    
      c775Status(tdc_id);
      tdc_status=1;
    
    
   printf(" Tst:  get events \n");
    
    for ( jj=0;  jj<50; jj++ ){

//  To add a wait of 35  the while statement just loops til satisfied
    retTime = time(0) + 3;   // Get finishing time.
    while (time(0) < retTime);
//   end of delay
        
   // printf(" Tst: done delay see what up time= %d \n", time(0)); *** caused error: %d expects type int but has type 'time_t'
      tdc_no_events=c775Dready(tdc_id);
     printf("Tst: TCD id= %d Count = %d  TDC events=  %d \n", tdc_id, jj, tdc_no_events);
   

           // qdc_no_events=c792Dready(tdc_id);
            /********* Dready

            vmeRead(&c775p[id]->status1)&C775_DATA_READY;    check if data
            C775_EXEC_READ_EVENT_COUNT(id);
             	s1 = c775p[id]->evCountL; \
 				s2 = c775p[id]->evCountH;  \
				c775EventCount[id] = (c775EventCount[id]&0xff000000) + (s2<<16) + (s1); \
				read register and set the varialbe based on the retrival
				return gives qdc_no_events=  nevts = c775EventCount[id] - c775EvtReadCnt[id];
								C775_EXEC_SET_EVTREADCNT(id,val)  sets areadcnt
								C775_EXEC_INCR_EVENT(id) {c775p[id]->incrEvent = 1; 
c775EvtReadCnt[id]++;}
								set to -1 on clears and resets
            ************/
       
        
         printf(" readout the events from buffer \n");
        
       while(tdc_no_events!=0){                     
                        // readout events start
            
            ndataTDC=c775ReadEvent(tdc_id, data);  // amount of data in the first qdc event
            no_MEB=ndataTDC;
            printf("Tst:  data in current event  value= %d  \n",ndataTDC);
            if (ndataTDC>0){
                for (i=0;i<ndataTDC;i++){
                printf("Tst:  data[ %d ]  value= %X  \n",i,data[i]);
                }   // read out ADC module into local array
              printf("Tst: i= %d, done cycling through data with %d total word in the event \n", i, no_MEB );
              c775_data_decode(data, no_MEB);
            }
            // printf("Tst: i= %d, done cycling through data with %d total word in the event \n", i, no_MEB );
            // c792_data_decode(data, no_MEB);
           tdc_no_events=c775Dready(tdc_id);
          // printf(" Tst:  check if any left after llop of efvents qdc_no_events QDC no events=  %d \n",  qdc_no_events);
        }
        c775Clear(tdc_id);
    }

    
CLOSE:

  vmeCloseDefaultWindows();

  return 0;
}

/*********
 
 #define C792_EXEC_SOFT_RESET(id) {c792p[id]->bitSet1 = C792_SOFT_RESET; c792p[id]->bitClear1 = C792_SOFT_RESET;}
 
 #define C792_EXEC_DATA_RESET(id) {c792p[id]->bitSet2 = C792_DATA_RESET; c792p[id]->bitClear2 = C792_DATA_RESET;}
 
 #define C792_SOFT_RESET    0x80
 #define C792_DATA_RESET    0x4

 ***********/
