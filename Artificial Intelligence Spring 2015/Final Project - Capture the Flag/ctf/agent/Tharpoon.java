package ctf.agent;

import java.lang.System;
import java.util.ArrayList;
import java.lang.Math;
import ctf.common.AgentAction;
import ctf.common.AgentEnvironment;
import ctf.agent.Agent;
import ctf.common.AgentAction;
import ctf.agent.TharpoonMap;

public class Tharpoon extends Agent {

    private static final int NORTH = 0;
    private static final int SOUTH = 1;
    private static final int EAST = 2;
    private static final int WEST = 3;

    private static int MAX_NUM_AGENTS = 2;

    private static int numAgents;

    private int agentNum;

    private static int[] spacesTravelledToBaseInPhaseOne = {1, 1};
    private boolean haveBothAgentsFoundTheBase = false;

    private static Boolean isBaseFound = false;
    private static Boolean[] hasAgentIFoundBase = {false, false};

    // booleans describing direction of goal
    // goal is either enemy flag, or our base
    private boolean goalNorth;
    private boolean goalSouth;
    private boolean goalEast;
    private boolean goalWest;

    private boolean obstNorth;
    private boolean obstSouth;
    private boolean obstEast;
    private boolean obstWest;

    private boolean enemyBaseNorth;
    private boolean enemyBaseSouth;
    private boolean enemyBaseEast;
    private boolean enemyBaseWest;

    //map stuff
    private static int knownMapHeight = 2;

    //global map so all agents know about our environment
    private static TharpoonMap globalMap;

    public Tharpoon(){
        //This is for resetting everything back to initial values in the case that the map is restarted.
        if(numAgents == MAX_NUM_AGENTS){
            numAgents = 0;
            knownMapHeight = 2;
            isBaseFound = false;
            hasAgentIFoundBase[0] = false;
            hasAgentIFoundBase[1] = false;
            spacesTravelledToBaseInPhaseOne[0] =1;
            spacesTravelledToBaseInPhaseOne[1] =1;
        }
        if(numAgents < MAX_NUM_AGENTS){
            // This is for adding a new Agent
            numAgents++;
            agentNum = numAgents;
            System.out.println("added agent " + agentNum);
        }

        hasAgentIFoundBase[agentNum - 1] = false;
    }

    // implements Agent.getMove() interface
    public int getMove( AgentEnvironment inEnvironment ) {

        if (haveBothAgentsFoundTheBase == false) {
            //PHASE ONE: (Find our base , start a map) at this point we know that the base is north or south of us because the agents are started on
            //the same column as the base as far north or south as possible.
            return checkForBase(inEnvironment);
        } else {
            return AgentAction.DO_NOTHING;
        }
    }

    public int checkForBase(AgentEnvironment inEnvironment){

        Boolean baseNorth = inEnvironment.isBaseNorth(inEnvironment.OUR_TEAM, false);
        Boolean baseSouth = inEnvironment.isBaseSouth(inEnvironment.OUR_TEAM, false);
        Boolean baseImmediatelyNorth = inEnvironment.isBaseNorth(inEnvironment.OUR_TEAM, true);
        Boolean baseImmediatelySouth = inEnvironment.isBaseSouth(inEnvironment.OUR_TEAM, true);

        if((baseNorth && baseImmediatelyNorth) || (baseSouth && baseImmediatelySouth)){
            //we know that the base is immediately above or below us
            knownMapHeight++;
            isBaseFound = true;
            hasAgentIFoundBase[agentNum - 1] = true;
            System.out.println("agent " + agentNum + " found the base");

            //we cannot build the global map unless both agents have found the base.  In the case that the
            //map has an even size one agent will find the base two turns before the other, and in the case
            //that the map is odd size one agent will find the base one turn before the other,
            //do nothing until the other agent finds the base
            //The agent that finds the base first will do nothing until the other agent finds the base.
            for(int i = 0; i < numAgents; i++){
                //System.out.print("a" + i + " found base: " + hasAgentIFoundBase[i]);
                System.out.println("but both agents have not found the base");
                if(hasAgentIFoundBase[i] == false){
                    return AgentAction.DO_NOTHING;
                }
            }System.out.println();

            haveBothAgentsFoundTheBase = true;
            System.out.println("both agents have now found the base");
            return caseBothAgentsHaveFoundTheBase(inEnvironment);
        }
        else {
            //We know that the base is north or south of us, and that we are not immediately next to it
            knownMapHeight++;
            spacesTravelledToBaseInPhaseOne[agentNum-1]++;
            System.out.println("agent " + agentNum + " moved " + ((baseNorth) ? ("north") : ("south")));
            return (baseNorth) ? (AgentAction.MOVE_NORTH) : (AgentAction.MOVE_SOUTH);
        }
    }

    public int caseBothAgentsHaveFoundTheBase(AgentEnvironment inEnvironment){
        System.out.println("boop");
        globalMap = new TharpoonMap(knownMapHeight - 1);
        int ourBaseX;
        int ourBaseY;

        //now we figure out what side of the map we are on by seeing if the enemy base is east or west
        enemyBaseEast = inEnvironment.isBaseEast(inEnvironment.ENEMY_TEAM, false);
        enemyBaseWest = inEnvironment.isBaseWest(inEnvironment.ENEMY_TEAM, false);

        //if our base is on the east, our base x coordinate is 0,
        //if on the west side, our base x coordinate is the size of the map - 1
        ourBaseX = (enemyBaseEast) ? (knownMapHeight -1) : (0);

        int whichAgentFoundBaseFirst;
        if(spacesTravelledToBaseInPhaseOne[0] == Math.min(spacesTravelledToBaseInPhaseOne[0], spacesTravelledToBaseInPhaseOne[1])){
            whichAgentFoundBaseFirst = 1;
        }else{
            whichAgentFoundBaseFirst = 2;
        }
        Boolean isAgentThatFoundBaseFirstNorthOfBase;
        if(agentNum == whichAgentFoundBaseFirst){
            isAgentThatFoundBaseFirstNorthOfBase = inEnvironment.isBaseSouth(inEnvironment.OUR_TEAM, false);
        }else{
            isAgentThatFoundBaseFirstNorthOfBase = !inEnvironment.isBaseSouth(inEnvironment.OUR_TEAM, false);
        }

        if(isAgentThatFoundBaseFirstNorthOfBase){
            ourBaseY = spacesTravelledToBaseInPhaseOne[whichAgentFoundBaseFirst];
        }
        else{
            ourBaseY = knownMapHeight - spacesTravelledToBaseInPhaseOne[whichAgentFoundBaseFirst - 1] - 1;
        }

        System.out.println("Our base was calculated to be: (" + ourBaseX + ", " + ourBaseY + ")");

        return AgentAction.DO_NOTHING;
    }
}