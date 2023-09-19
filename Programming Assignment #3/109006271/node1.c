
#include <stdio.h>

struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;
extern void tolayer2(struct rtpkt packet);

struct distance_table 
{
  int costs[4][4];
} dt1;


extern void read1(FILE *file)
{
  //  Initialize distance_table to 999
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt1.costs[i][j] = 999;
    }
  }

  char *line = NULL;
  size_t len = 0;

  // Read file
  getline(&line, &len, file);
  sscanf(line, "%d %d %d %d", &dt1.costs[0][0], &dt1.costs[1][1], &dt1.costs[2][2], &dt1.costs[3][3]);
}

extern void rtinit1() 
{
  /*TODO*/
  int i;
	dt1.costs[0][0] = 1;
	dt1.costs[0][1] = 1;
	dt1.costs[1][1] = 0;
	dt1.costs[2][1] = 1;
	dt1.costs[2][2] = 1;


	struct rtpkt packet0, packet2;
	packet0.sourceid = 1;
	packet0.destid = 0;
	packet2.sourceid = 1;
	packet2.destid = 2;

	for (i = 0; i < 4; i++){
		packet0.mincost[i] = dt1.costs[i][1];
		packet2.mincost[i] = dt1.costs[i][1];
	}
	tolayer2(packet0);
	tolayer2(packet2);

}

extern void rtupdate1(struct rtpkt *rcvdpkt)
{
  /* TODO */

	int j = rcvdpkt->sourceid;
	int flag = 0;	
  int temp1,temp2;
  int i;
	for (i = 0; i < 4; i++){
		if (dt1.costs[i][j] > dt1.costs[j][1] + rcvdpkt->mincost[i])
		{
			dt1.costs[i][j] = dt1.costs[j][1] + rcvdpkt->mincost[i];
			if(i != 1){
				flag = 1;
      }
		}
	}
	if (flag == 1){
		struct rtpkt packet0, packet2;
    
		packet0.sourceid = 1;
		packet0.destid = 0;

		packet2.sourceid = 1;
		packet2.destid = 2;

		packet0.mincost[1] = 0;
		packet2.mincost[1] = 0;
		
		for (i = 0; i < 4; i++){
      temp1 = (dt1.costs[i][0] <= dt1.costs[i][2] ? dt1.costs[i][0] : dt1.costs[i][2]);
      temp1 = (temp1 <= dt1.costs[i][3] ? temp1 : dt1.costs[i][3]);
      packet0.mincost[i] = temp1;
			
      temp2 = (dt1.costs[i][0] <= dt1.costs[i][2] ? dt1.costs[i][0] : dt1.costs[i][2]);
      temp2 = (temp2 <= dt1.costs[i][3] ? temp2 : dt1.costs[i][3]);
      packet2.mincost[i] = temp2;
		}
		tolayer2(packet0);
		tolayer2(packet2);
	}
}

void printdt1(void)  
{
  struct distance_table *dtptr = &dt1;

  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}

extern void linkhandler1(int linkid, int newcost)
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
{
  /* TODO */


}

extern void print_min_cost1()
{

  int min_cost[4];

  for (int i = 0; i < 4; i++)
  {
    int min = dt1.costs[i][i];
    for (int j = 0; j < 4; j++)
    {
      min = min > dt1.costs[i][j] ? dt1.costs[i][j] : min;
    }

    min_cost[i] = min;
  }

  printf("Min cost %d : %d %d %d %d\n", 1, min_cost[0], min_cost[1],
         min_cost[2], min_cost[3]);
}