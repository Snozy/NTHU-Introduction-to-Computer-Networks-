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
} dt2;


extern void read2(FILE *file)
{
  //  Initialize distance_table to 999
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt2.costs[i][j] = 999;
    }
  }

  char *line = NULL;
  size_t len = 0;

  // Read file
  getline(&line, &len, file);
  sscanf(line, "%d %d %d %d", &dt2.costs[0][0], &dt2.costs[1][1], &dt2.costs[2][2], &dt2.costs[3][3]);

}

extern void rtinit2(){
    /* TODO */
	int i;
	dt2.costs[0][0] = 3;
	dt2.costs[0][2] = 3;
	dt2.costs[1][1] = 1;
	dt2.costs[1][2] = 1;
	dt2.costs[2][2] = 0;
	dt2.costs[3][2] = 2;
	dt2.costs[3][3] = 2;
	

	struct rtpkt packet0, packet1, packet3;
	packet0.sourceid = 2;
	packet0.destid = 0;
	packet1.sourceid = 2;
	packet1.destid = 1;
	packet3.sourceid = 2;
	packet3.destid = 3;

	for (i = 0; i < 4; i++){
		packet0.mincost[i] = dt2.costs[i][2];
		packet1.mincost[i] = dt2.costs[i][2];
		packet3.mincost[i] = dt2.costs[i][2];
	}

	tolayer2(packet0);
	tolayer2(packet1);
	tolayer2(packet3);

}

extern void rtupdate2(struct rtpkt *rcvdpkt)
{
  /* TODO */
	int j = rcvdpkt->sourceid;	
	int flag = 0;		
  	int temp1,temp2,temp3;
	int i;
	for (int i = 0; i < 4; i++){
		if (dt2.costs[i][j] > dt2.costs[j][2] + rcvdpkt->mincost[i]){
			dt2.costs[i][j] = dt2.costs[j][2] + rcvdpkt->mincost[i];
			if(i != 2){
				flag = 1;
			}
		}
	}
	if (flag == 1) {
		struct rtpkt packet0, packet1, packet3;
		
		packet0.sourceid = 2;
		packet0.destid = 0;

		packet1.sourceid = 2;
		packet1.destid = 1;

		packet3.sourceid = 2;
		packet3.destid = 3;

		packet0.mincost[2] = 0;
		packet1.mincost[2] = 0;
		packet3.mincost[2] = 0;

		for (i = 0; i < 4; i++){
			temp1 = (dt2.costs[i][0] <= dt2.costs[i][1] ? dt2.costs[i][0] : dt2.costs[i][1]);
			temp1 = (temp1 <= dt2.costs[i][3] ? temp1 : dt2.costs[i][3]);
			packet0.mincost[i] = temp1;

			temp2 = (dt2.costs[i][0] <= dt2.costs[i][1] ? dt2.costs[i][0] : dt2.costs[i][1]);
			temp2 = (temp2 <= dt2.costs[i][3] ? temp2 : dt2.costs[i][3]);
			packet1.mincost[i] = temp2;

			temp3 = (dt2.costs[i][0] <= dt2.costs[i][1] ? dt2.costs[i][0] : dt2.costs[i][1]);
			temp3 = (temp3 <= dt2.costs[i][3] ? temp3 : dt2.costs[i][3]);
			packet3.mincost[i] = temp3;
		}
		tolayer2(packet0);
		tolayer2(packet1);
		tolayer2(packet3);
	}
}

void printdt2(void) 
{
  struct distance_table *dtptr = &dt2;

  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}

extern void print_min_cost2()
{

  int min_cost[4];

  for (int i = 0; i < 4; i++)
  {
    int min = dt2.costs[i][i];
    for (int j = 0; j < 4; j++)
    {
      min = min > dt2.costs[i][j] ? dt2.costs[i][j] : min;
    }

    min_cost[i] = min;
  }

  printf("Min cost %d : %d %d %d %d\n", 2, min_cost[0], min_cost[1],
         min_cost[2], min_cost[3]);
}
