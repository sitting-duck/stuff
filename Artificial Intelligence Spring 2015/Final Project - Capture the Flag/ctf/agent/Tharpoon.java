package ctf.agent;


import ctf.common.AgentEnvironment;
import ctf.agent.Agent;

import java.lang.System;
import java.util.ArrayList;

import ctf.common.AgentAction;

public class Tharpoon extends Agent {

    private static int MAX_NUM_AGENTS = 2;

    private static int numAgents;

    private int agentNum;

    private Boolean isBaseFound = false;

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

    //map stuff
    private static int knownMapHeight = 0;
    private static int knownMapLength = 0;

    //local map for keeping track of stuff until we make the global map
    private ArrayList<ArrayList<String>> localMap;

    //global map so all agents know about our environment
    private ArrayList<ArrayList<String>> globalMap;

    public Tharpoon(){
        if(numAgents == MAX_NUM_AGENTS){
            numAgents = 0;
            private static int knownMapHeight = 0;
            private static int knownMapLength = 0;
        }
        if(numAgents < MAX_NUM_AGENTS){
            numAgents++;
            agentNum = numAgents;
            System.out.println("added agent " + agentNum);
        }
    }

    // implements Agent.getMove() interface
    public int getMove( AgentEnvironment inEnvironment ) {

        if(isBaseFound == false){
            //at this point we know that the base is north or south of us because the agents are started on
            //the same column as the base as far north or south as possible.

            //check to see if the base is north of us
            if(inEnvironment.isFlagNorth(inEnvironment.ENEMY_TEAM, false )){

                //since it's north of us, check if it's immediately north of us
                if(inEnvironment.isFlagNorth(inEnvironment.ENEMY_TEAM, true ) == false){
                    //if the base was not immediately north of us then we have to get to it so we decide to go north
                    
                    return MOVE_NORTH;
                }
                else{
                    //if it's immediately north of us we add our current knowledge to the global map

                }
            }

        }



        //if this agent doesn't have the enemy flag
        if( !inEnvironment.hasFlag() ) {
            // make goal the enemy flag
            goalNorth = inEnvironment.isFlagNorth(
                    inEnvironment.ENEMY_TEAM, false );

            goalSouth = inEnvironment.isFlagSouth(
                    inEnvironment.ENEMY_TEAM, false );

            goalEast = inEnvironment.isFlagEast(
                    inEnvironment.ENEMY_TEAM, false );

            goalWest = inEnvironment.isFlagWest(
                    inEnvironment.ENEMY_TEAM, false );
        }
        else {
            // we have enemy flag.
            // make goal our base
            goalNorth = inEnvironment.isBaseNorth(
                    inEnvironment.OUR_TEAM, false );

            goalSouth = inEnvironment.isBaseSouth(
                    inEnvironment.OUR_TEAM, false );

            goalEast = inEnvironment.isBaseEast(
                    inEnvironment.OUR_TEAM, false );

            goalWest = inEnvironment.isBaseWest(
                    inEnvironment.OUR_TEAM, false );
        }

        // now we have direction booleans for our goal

        // check for immediate obstacles blocking our path
        obstNorth = inEnvironment.isObstacleNorthImmediate();
        obstSouth = inEnvironment.isObstacleSouthImmediate();
        obstEast = inEnvironment.isObstacleEastImmediate();
        obstWest = inEnvironment.isObstacleWestImmediate();


        // if the goal is north only, and we're not blocked
        if( goalNorth && ! goalEast && ! goalWest && !obstNorth ) {
            // move north
            return AgentAction.MOVE_NORTH;
        }

        // if goal both north and east
        if( goalNorth && goalEast ) {
            // pick north or east for move with 50/50 chance
            if( Math.random() < 0.5 && !obstNorth ) {
                return AgentAction.MOVE_NORTH;
            }
            if( !obstEast ) {
                return AgentAction.MOVE_EAST;
            }
            if( !obstNorth ) {
                return AgentAction.MOVE_NORTH;
            }
        }

        // if goal both north and west
        if( goalNorth && goalWest ) {
            // pick north or west for move with 50/50 chance
            if( Math.random() < 0.5 && !obstNorth ) {
                return AgentAction.MOVE_NORTH;
            }
            if( !obstWest ) {
                return AgentAction.MOVE_WEST;
            }
            if( !obstNorth ) {
                return AgentAction.MOVE_NORTH;
            }
        }

        // if the goal is south only, and we're not blocked
        if( goalSouth && ! goalEast && ! goalWest && !obstSouth ) {
            // move south
            return AgentAction.MOVE_SOUTH;
        }

        // do same for southeast and southwest as for north versions
        if( goalSouth && goalEast ) {
            if( Math.random() < 0.5 && !obstSouth ) {
                return AgentAction.MOVE_SOUTH;
            }
            if( !obstEast ) {
                return AgentAction.MOVE_EAST;
            }
            if( !obstSouth ) {
                return AgentAction.MOVE_SOUTH;
            }
        }

        if( goalSouth && goalWest && !obstSouth ) {
            if( Math.random() < 0.5 ) {
                return AgentAction.MOVE_SOUTH;
            }
            if( !obstWest ) {
                return AgentAction.MOVE_WEST;
            }
            if( !obstSouth ) {
                return AgentAction.MOVE_SOUTH;
            }
        }

        // if the goal is east only, and we're not blocked
        if( goalEast && !obstEast ) {
            return AgentAction.MOVE_EAST;
        }

        // if the goal is west only, and we're not blocked
        if( goalWest && !obstWest ) {
            return AgentAction.MOVE_WEST;
        }

        // otherwise, make any unblocked move
        if( !obstNorth ) {
            return AgentAction.MOVE_NORTH;
        }
        else if( !obstSouth ) {
            return AgentAction.MOVE_SOUTH;
        }
        else if( !obstEast ) {
            return AgentAction.MOVE_EAST;
        }
        else if( !obstWest ) {
            return AgentAction.MOVE_WEST;
        }
        else {
            // completely blocked!
            return AgentAction.DO_NOTHING;
        }
    }
}