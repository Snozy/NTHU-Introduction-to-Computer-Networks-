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
  int costs[4][4] ;
} dt0;


extern void read0(FILE *file)
{

  //  Initialize distance_table to 999
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt0.costs[i][j] = 999;
    }
  }
  char *line = NULL;
  size_t len = 0;

  // Read file
  getline(&line, &len, file);
  sscanf(line, "%d %d %d %d", &dt0.costs[0][0], &dt0.costs[1][1], &dt0.costs[2][2], &dt0.costs[3][3]);
}


void rtinit0(){
	/* TODO */
  int i;	
	/*updating the costs for each network */
	dt0.costs[0][0] = 0;
	dt0.costs[1][0] = 1;
	dt0.costs[1][1] = 1;
	dt0.costs[2][0] = 3;
	dt0.costs[2][2] = 3;
	dt0.costs[3][0] = 7;
	dt0.costs[3][3] = 7;

	/*making packets to send to neighbours*/
	struct rtpkt packet1, packet2, packet3;
	packet1.sourceid = 0;
  packet2.sourceid = 0;
	packet3.sourceid = 0;
	packet1.destid = 1;
	packet2.destid = 2;
	packet3.destid = 3;

  //updating packet costs
	for (i = 0; i < 4; i++){
		packet1.mincost[i] = dt0.costs[i][0];
		packet2.mincost[i] = dt0.costs[i][0];
		packet3.mincost[i] = dt0.costs[i][0];
	}
	
	/*sending packets to neighbours*/
	tolayer2(packet1);
	tolayer2(packet2);
	tolayer2(packet3);
}


extern void rtupdate0(struct rtpkt *rcvdpkt)
{
  /* TODO */
	

	int j = rcvdpkt->sourceid;	/*getting source id*/
	int flag = 0;		/*there is no change when flag is 0*/
	int temp1,temp2,temp3; /*temp for updating the min values*/

	/*traversing column to see there is a flag*/
	for (int i = 0; i < 4; i++){
		if (dt0.costs[i][j] > dt0.costs[j][0]+ rcvdpkt->mincost[i]){
			dt0.costs[i][j] = dt0.costs[j][0] + rcvdpkt->mincost[i];
			if(i != 0){
				flag = 1;
      }
		}
	}

  //checking if there is change
	if (flag == 1){
		struct rtpkt packet1, packet2, packet3;
    /*inilization of packets to send*/
		packet1.sourceid = 0;
    packet2.sourceid = 0;
    packet3.sourceid = 0;

		packet1.destid = 1;
		packet2.destid = 2;
		packet3.destid = 3;

		packet1.mincost[0] = 0;
		packet2.mincost[0] = 0;
		packet3.mincost[0] = 0;

    /*Updating the min values for each packets to send*/
		for (int i = 1; i < 4; i++){
      temp1 = (dt0.costs[i][1] <= dt0.costs[i][2] ? dt0.costs[i][1] : dt0.costs[i][2]);
      temp1 = (temp1 <= dt0.costs[i][3] ? temp1 : dt0.costs[i][3]);
      packet1.mincost[i] = temp1;

      temp2 = (dt0.costs[i][1] <= dt0.costs[i][2] ? dt0.costs[i][1] : dt0.costs[i][2]);
      temp2 = (temp2 <= dt0.costs[i][3] ? temp2 : dt0.costs[i][3]);
      packet2.mincost[i] = temp2;

      temp3 = (dt0.costs[i][1] <= dt0.costs[i][2] ? dt0.costs[i][1] : dt0.costs[i][2]);
      temp3 = (temp3 <= dt0.costs[i][3] ? temp3 : dt0.costs[i][3]);
      packet3.mincost[i] = temp3;
		}
  /*sending packets*/
  tolayer2(packet1);
  tolayer2(packet2);
  tolayer2(packet3);
  }
}

 void printdt0(void) 
{
  struct distance_table *dtptr = &dt0;
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n", dtptr->costs[1][1],
           dtptr->costs[1][2], dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n", dtptr->costs[2][1],
           dtptr->costs[2][2], dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][1],
           dtptr->costs[3][2], dtptr->costs[3][3]);
}

extern void linkhandler0(int linkid, int newcost)
/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
{
  /* TODO */

    
}

extern void print_min_cost0()
{
  int min_cost[4];

  for(int i = 0;i < 4;i++)
  {
    int min = dt0.costs[i][i];
    for(int j = 0;j < 4; j++)
    {
      min = min > dt0.costs[i][j] ? dt0.costs[i][j] : min;
    }

    min_cost[i] = min;
  }

  printf("Min cost %d : %d %d %d %d\n", 0, min_cost[0], min_cost[1], min_cost[2], min_cost[3]);
}

