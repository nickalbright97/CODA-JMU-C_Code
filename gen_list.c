#define ROL_NAME__ "GEN_USER"
#define MAX_EVENT_LENGTH 32768
#define MAX_EVENT_POOL   100
/* POLLING_MODE */
#define POLLING___
#define POLLING_MODE
#define GEN_MODE
#define INIT_NAME gen_list__init
#include <rol.h>
#include <GEN_source.h>
#define TRIG_ADDR 0x3800
#define TRIG_INPUT 1
#define DAQ_MODE S3610_INIT_DAQ_MODE_POLLING
extern int bigendian_out;
int blklevel = 1;
int ndatawords = 10;
int trigBankType = 0xff11;
static void __download()
{
    daLogMsg("INFO","Readout list compiled %s", DAYTIME);
#ifdef POLLING___
   rol->poll = 1;
#endif
    *(rol->async_roc) = 0; /* Normal ROC */
  {  /* begin user */
{/* inline c-code */
 
  bigendian_out = 1;
  vmeOpenDefaultWindows();

  /* Initialize sis3610 */
  s3610Init(TRIG_ADDR, 0, 0, DAQ_MODE);
  s3610Status(0, 0);
  GENPollValue = TRIG_INPUT;
	    
 
 }/*end inline c-code */
    daLogMsg("INFO","User Download Executed");

  }  /* end user */
} /*end download */     

static void __prestart()
{
CTRIGINIT;
    *(rol->nevents) = 0;
  {  /* begin user */
unsigned long jj, adc_id;
    daLogMsg("INFO","Entering User Prestart");

    GEN_INIT;
    CTRIGRSS(GEN,1,usrtrig,usrtrig_done);
    CRTTYPE(1,GEN,1);
    daLogMsg("INFO","User Prestart Executed");

  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
    *(rol->nevents) = 0;
    rol->recNb = 0;
} /*end prestart */     

static void __end()
{
  {  /* begin user */
  CDODISABLE(GEN,1,0);
{/* inline c-code */
 
{
  s3610Status(0, 0);
}
 
 }/*end inline c-code */
    daLogMsg("INFO","User End Executed");

  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
} /* end end block */

static void __pause()
{
  {  /* begin user */
  CDODISABLE(GEN,1,0);
    daLogMsg("INFO","User Pause Executed");

  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
} /*end pause */
static void __go()
{

  {  /* begin user */
    daLogMsg("INFO","Entering User Go");

  s3610Status(0, 0);
  CDOENABLE(GEN,1,1);
  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
}

void usrtrig(unsigned long EVTYPE,unsigned long EVSOURCE)
{
    long EVENT_LENGTH;
  {  /* begin user */
unsigned long ii, evtnum;
 evtnum = *(rol->nevents);
 CEOPEN(ROCID,BT_BANK,blklevel);
 InsertDummyTriggerBank(trigBankType,evtnum,EVTYPE,blklevel);
 CBOPEN(1,BT_UI4,blklevel);
    CBWRITE32(0xda000011); 
{/* inline c-code */
 
   /* This is dummy data */
   for(ii=0;ii<ndatawords;ii++) {
     *rol->dabufp++ = ii;
   }
 
 }/*end inline c-code */
    CBWRITE32(0xda0000ff); 
 CBCLOSE;
 CECLOSE;
  }  /* end user */
} /*end trigger */

void usrtrig_done()
{
  {  /* begin user */
  }  /* end user */
} /*end done */

void __done()
{
poolEmpty = 0; /* global Done, Buffers have been freed */
  {  /* begin user */
  s3610IntAck(TRIG_INPUT);
  }  /* end user */
} /*end done */

void __reset () 
{
{/* inline c-code */
 
  printf("Reset: ROC Cleanup\n");

 
 }/*end inline c-code */
} /* end of user codes */

/* inline c-code */
 
__attribute__((destructor)) void end (void)
{
  printf("ROC Cleanup\n");
  vmeCloseDefaultWindows();
}
 
 /*end inline c-code */
