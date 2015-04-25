package ctf.agent;

import java.lang.Integer;
import java.lang.System;
import java.util.ArrayList;
import java.lang.Math;
import ctf.common.AgentAction;
import ctf.common.AgentEnvironment;
import ctf.agent.Agent;
import ctf.common.AgentAction;

public class Tharpoon extends Agent {

    public char[][] map;
    private Coordinate<Integer> mySpawn;
    private Coordinate<Integer> myPosition;

    private static int MAX_NUM_AGENTS = 2;
    private static int numAgents;
    private int agentNum;
    private boolean hasFlag;

    private static int[] seekBaseDistance = {1, 1};
    private static boolean haveBothAgentsFoundTheBase = false;

    private static Boolean isBaseFound = false;
    private static Boolean[] hasAgentIFoundBase = {false, false};

    private boolean obstNorth;
    private boolean obstSouth;
    private boolean obstEast;
    private boolean obstWest;

    private boolean ourBaseNorth;
    private boolean ourBaseSouth;
    private boolean ourBaseWest;
    private boolean ourBaseEast;

    private boolean ourBaseNorthImmediate;
    private boolean ourBaseSouthImmediate;
    private boolean ourBaseWestImmediate;
    private boolean ourBaseEastImmediate;

    private boolean enemyBaseNorth;
    private boolean enemyBaseSouth;
    private boolean enemyBaseEast;
    private boolean enemyBaseWest;

    private boolean enemyBaseNorthImmediate;
    private boolean enemyBaseSouthImmediate;
    private boolean enemyBaseEastImmediate;
    private boolean enemyBaseWestImmediate;

    boolean enemyNorthImmediate;
    boolean enemyEastImmediate;
    boolean enemySouthImmediate;
    boolean enemyWestImmediate;

    //map stuff
    private static int knownMapHeight = 2;
    private static boolean mapInitialized = false;

    Place ourBase;
    Place enemyBase;
    ArrayList<Place> pointsOfInterest;
    private int ourBaseX;
    private int ourBaseY;
    private int enemyBaseX;
    private int enemyBaseY;
    private static ArrayList<Coordinate<Integer>> agentPositions;

    private enum direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST}
    private enum state {INITIALIZE, SEEK_ENEMY_BASE, SEEK_OUR_BASE, RETRIEVE_FRIENDLY_FLAG }
    private state currentState;

    public class Place{
        Place(String name){this.name = name;}
        String name;
        direction dir;
        Coordinate<Integer> position;
    }

    public class Coordinate<N> {
        public N x;
        public N y;
        public Coordinate(){}
        public Coordinate(N x, N y){this.x = x; this.y = y;}
        public void set(N x, N y) {this.x = x; this.y = y; }
    }

    public Tharpoon(){

        //This is for resetting everything back to initial values in the case that the map is restarted.
        if(numAgents == MAX_NUM_AGENTS){
            numAgents = 0;
            knownMapHeight = 2;
            isBaseFound = false;
            hasAgentIFoundBase[0] = false;
            hasAgentIFoundBase[1] = false;
            seekBaseDistance[0] =1;
            seekBaseDistance[1] =1;
            haveBothAgentsFoundTheBase = false;
        }
        if(numAgents < MAX_NUM_AGENTS){
            // This is for adding a new Agent
            numAgents++;
            agentNum = numAgents;
            System.out.println("added agent " + agentNum);
        }

        hasAgentIFoundBase[agentNum - 1] = false;
        currentState = state.INITIALIZE;

        mySpawn = new Coordinate<Integer>();
        myPosition = new Coordinate<Integer>();
        agentPositions = new ArrayList<Coordinate<Integer>>();
        for(int i = 0; i < MAX_NUM_AGENTS; i++){
            agentPositions.add(new Coordinate<Integer>());
        }
        ourBase = new Place("ourBase");
        enemyBase = new Place("enemyBase");
        pointsOfInterest = new ArrayList<Place>();

        pointsOfInterest.add(ourBase);
        pointsOfInterest.add(enemyBase);
    }

    public int getMove( AgentEnvironment inEnvironment ) {
        int whatToDo = AgentAction.DO_NOTHING;
        queryEnvironment(inEnvironment);

        switch(currentState){
            case INITIALIZE:
                if(haveBothAgentsFoundTheBase == false){
                    whatToDo = seekBase_InitializeMap(inEnvironment);
                }
                else{
                    currentState = state.SEEK_ENEMY_BASE;
                    System.out.println(" agent " + agentNum + " current state is SEEK_ENEMY_BASE");
                }
                break;

            case SEEK_ENEMY_BASE:
                printPointsOfInterest();
                whatToDo = seek(enemyBase);
                break;

            case SEEK_OUR_BASE:
                printPointsOfInterest();
                whatToDo = seek(ourBase);
                break;

            default:
                System.out.println("Agent " + agentNum + " stayed still");
                whatToDo = AgentAction.DO_NOTHING;
                break;
        }
        System.out.println("agent " + agentNum + " " + getNameFromAgentAction(whatToDo));
        return whatToDo;
    }

    public int seek(Place place){
        int whatToDo = AgentAction.DO_NOTHING;

        if(hasFlag){
            currentState = state.SEEK_OUR_BASE;
            place = ourBase;
        }else{
            currentState = state.SEEK_ENEMY_BASE;
            place = enemyBase;
        }

        switch(place.dir){
            case NORTH:
                if(!obstNorth) {
                    if (!hasFlag || !enemyNorthImmediate) {
                        whatToDo = AgentAction.MOVE_NORTH;
                    }else if(!hasFlag || !enemyEastImmediate){
                        whatToDo = AgentAction.MOVE_EAST;
                    } else if(!hasFlag || !enemyWestImmediate){
                        whatToDo = AgentAction.MOVE_WEST;
                    }else if(!hasFlag || !enemySouthImmediate){
                        whatToDo = AgentAction.MOVE_SOUTH;
                    }else{
                        whatToDo = AgentAction.DO_NOTHING;
                    }
                }else if(Math.random() < 0.5 && !obstEast){
                    whatToDo = AgentAction.MOVE_EAST;
                }else if(!obstWest){
                    whatToDo = AgentAction.MOVE_WEST;
                }else{
                    whatToDo = AgentAction.MOVE_SOUTH;
                }
                break;
            case NORTHEAST:
                /*if(!obstNorth && !obstEast){
                    whatToDo = (Math.random() < 0.75) ? (AgentAction.MOVE_EAST) : (AgentAction.MOVE_NORTH);
                }else{
                    if(!obstWest){
                        whatToDo = AgentAction.MOVE_WEST;
                    }
                    else{
                        whatToDo = AgentAction.MOVE_EAST;
                    }
                }*/

                if(!obstEast){
                    whatToDo = AgentAction.MOVE_EAST;
                }else if(!obstNorth){
                    whatToDo = AgentAction.MOVE_NORTH;
                }else if(!obstSouth){
                    whatToDo = AgentAction.MOVE_SOUTH;
                }else if(!obstWest){
                    whatToDo = AgentAction.MOVE_WEST;
                }
                break;
            case EAST:
                if(!obstEast) {
                    if (!hasFlag || !enemyEastImmediate) {
                        whatToDo = AgentAction.MOVE_EAST;
                    }else if(!hasFlag || !enemyNorthImmediate){
                        whatToDo = AgentAction.MOVE_NORTH;
                    } else if(!hasFlag || !enemySouthImmediate){
                        whatToDo = AgentAction.MOVE_SOUTH;
                    }else if(!hasFlag || !enemyWestImmediate){
                        whatToDo = AgentAction.MOVE_WEST;
                    }else{
                        whatToDo = AgentAction.DO_NOTHING;
                    }
                }else if(Math.random() < 0.5 && !obstNorth){
                    whatToDo = AgentAction.MOVE_NORTH;
                }
                else if(!obstSouth){
                    whatToDo = AgentAction.MOVE_SOUTH;
                }
                else{
                    whatToDo = AgentAction.MOVE_WEST;
                }
                break;
            case SOUTHEAST:
                /*if(!obstSouth && !obstEast){
                    whatToDo = (Math.random() < 0.75) ? (AgentAction.MOVE_EAST) : (AgentAction.MOVE_SOUTH);
                }else{
                    if(!obstWest){
                        whatToDo = AgentAction.MOVE_WEST;
                    }
                    else{
                        whatToDo = AgentAction.MOVE_NORTH;
                    }
                }*/
                if(!obstEast){
                    whatToDo = AgentAction.MOVE_EAST;
                }else if(!obstSouth){
                    whatToDo = AgentAction.MOVE_SOUTH;
                }else if(!obstNorth){
                whatToDo = AgentAction.MOVE_NORTH;
                }else if(!obstWest){
                    whatToDo = AgentAction.MOVE_WEST;
                }
                break;
            case SOUTH:
                if(!obstSouth){
                    if (!hasFlag || !enemySouthImmediate) {
                        whatToDo = AgentAction.MOVE_SOUTH;
                    }else if(!hasFlag || !enemyEastImmediate){
                        whatToDo = AgentAction.MOVE_EAST;
                    } else if(!hasFlag || !enemyWestImmediate){
                        whatToDo = AgentAction.MOVE_WEST;
                    }else if(!hasFlag || !enemyNorthImmediate){
                        whatToDo = AgentAction.MOVE_NORTH;
                    }else{
                        whatToDo = AgentAction.DO_NOTHING;
                    }
                }
                else if(Math.random() < 0.5 && !obstEast){
                    whatToDo = AgentAction.MOVE_EAST;
                }
                else if(!obstWest){
                    whatToDo = AgentAction.MOVE_WEST;
                }
                else{
                    whatToDo = AgentAction.MOVE_NORTH;
                }
                break;
            case SOUTHWEST:
                /*if(!obstSouth && !obstWest){
                    whatToDo = (Math.random() < 0.75) ? (AgentAction.MOVE_WEST) : (AgentAction.MOVE_SOUTH);
                }else{
                    if(!obstEast){
                        whatToDo = AgentAction.MOVE_EAST;
                    }
                    else{
                        whatToDo = AgentAction.MOVE_NORTH;
                    }
                }*/
                if(!obstWest){
                    whatToDo = AgentAction.MOVE_WEST;
                }else if(!obstSouth){
                    whatToDo = AgentAction.MOVE_SOUTH;
                }else if(!obstNorth){
                    whatToDo = AgentAction.MOVE_NORTH;
                }else if(!obstEast){
                    whatToDo = AgentAction.MOVE_EAST;
                }
                break;
            case WEST:
                if(!obstWest){
                    if (!hasFlag || !enemyWestImmediate) {
                        whatToDo = AgentAction.MOVE_WEST;
                    }else if(!hasFlag || !enemyNorthImmediate){
                        whatToDo = AgentAction.MOVE_NORTH;
                    } else if(!hasFlag || !enemySouthImmediate){
                        whatToDo = AgentAction.MOVE_SOUTH;
                    }else if(!hasFlag || !enemyEastImmediate){
                        whatToDo = AgentAction.MOVE_EAST;
                    }else{
                        whatToDo = AgentAction.DO_NOTHING;
                    }
                }else if(Math.random() < 0.5 && !obstNorth){
                    whatToDo = AgentAction.MOVE_NORTH;
                }
                else if(!obstSouth){
                    whatToDo = AgentAction.MOVE_SOUTH;
                }else{
                    whatToDo = AgentAction.MOVE_EAST;
                }
                break;
            case NORTHWEST:
                /*if(!obstNorth && !obstWest){
                    whatToDo = (Math.random() < 0.75) ? (AgentAction.MOVE_WEST) : (AgentAction.MOVE_NORTH);
                }else{
                    if(!obstEast){
                        whatToDo = AgentAction.MOVE_EAST;
                    }
                    else{
                        whatToDo = AgentAction.MOVE_SOUTH;
                    }
                }*/
                if(!obstNorth){
                    whatToDo = AgentAction.MOVE_NORTH;
                }else if(!obstWest){
                    whatToDo = AgentAction.MOVE_WEST;
                }else if(!obstSouth){
                    whatToDo = AgentAction.MOVE_SOUTH;
                }else if(!obstEast){
                    whatToDo = AgentAction.MOVE_EAST;
                }
                break;
        }
        return whatToDo;
    }

    public String getNameFromAgentAction(int action){
        String name = "does nothing";

        switch(action){
            case AgentAction.MOVE_NORTH:
                name = "moves north";
                break;
            case AgentAction.MOVE_EAST:
                name = "moves east";
                break;
            case AgentAction.MOVE_SOUTH:
                name = "moves south";
                break;
            case AgentAction.MOVE_WEST:
                name = "moves west";
                break;
            case AgentAction.PLANT_HYPERDEADLY_PROXIMITY_MINE:
                name = "plants a mine";
                break;
        }
        return name;
    }

    public int seekBase_InitializeMap(AgentEnvironment inEnvironment){

        if((ourBaseNorthImmediate || ourBaseSouthImmediate) && (hasAgentIFoundBase[agentNum - 1] == false)) {
            return oneAgentFoundBase(inEnvironment);
        }
        if(ourBaseNorth||ourBaseSouth && (hasAgentIFoundBase[agentNum - 1] == false)) {
             //We know that the base is north or south of us, and that we are not immediately next to it

            knownMapHeight++;
            seekBaseDistance[agentNum - 1]++;
             System.out.println("agent " + agentNum + " moved " + ((ourBaseNorth) ? ("north") : ("south")));
             return (ourBaseNorth) ? (AgentAction.MOVE_NORTH) : (AgentAction.MOVE_SOUTH);
        }
        System.out.println("Agent " + agentNum + " stayed still");
        return AgentAction.DO_NOTHING;
    }

    public int oneAgentFoundBase(AgentEnvironment inEnvironment){
        //we know that the base is immediately above or below us
        knownMapHeight++;
        hasAgentIFoundBase[agentNum - 1] = true;
        System.out.println("agent " + agentNum + " found the base");

        setMySpawn(inEnvironment);

        for (int i = 0; i < numAgents; i++) {
            //System.out.print("a" + i + " found base: " + hasAgentIFoundBase[i]);
            if (hasAgentIFoundBase[i] == false) {
                System.out.println("but the other agent has not found the base");
                System.out.println("Agent " + agentNum + "Stayed still");
                return AgentAction.DO_NOTHING;
            }
        }
        return bothAgentsFoundBase(inEnvironment);
    }

    public int bothAgentsFoundBase(AgentEnvironment inEnvironment){
        haveBothAgentsFoundTheBase = true;
        System.out.println("both agents have now found the base");
        map = makeEmptyMap();
        setBaseCoordinates();
        setMyPosition();
        setAgentPositions();
        mapInitialized = true;
        return seek(enemyBase);
    }

    public void setAgentPositions(){
        agentPositions.get(agentNum - 1).set(myPosition.x, myPosition.y);
        setMapSquare(myPosition, 'a');
        System.out.println("agent " + agentNum + " has position (" + myPosition.x + ", " + myPosition.y + ")");
        int otherAgent = (agentNum == 1) ? (2) : (1);
        Integer otherAgentY = (ourBaseSouth) ? (myPosition.y + 2) : (myPosition.y -2);
        agentPositions.get(otherAgent - 1).set(myPosition.x, otherAgentY);
        setMapSquare(agentPositions.get(otherAgent-1), 'a');
        System.out.println("agent " + otherAgent + " has position (" + myPosition.x + ", " + otherAgentY + ")");
    }

    public void setMyPosition(){
        myPosition.x = (enemyBaseEast) ? (1) : (knownMapHeight);
        myPosition.y = (ourBaseNorth) ? (ourBaseY + 1) : (ourBaseY - 1);
    }

    public void setMapSquare(Coordinate<Integer> pos, char c){
        map[pos.x -1][pos.y-1] = c;
    }

    public void setBaseCoordinates(){
        int firstAgent = whichAgentFoundBaseFirst();
        boolean firstAgentNorth = (agentNum == firstAgent) ? (ourBaseSouth) : (!ourBaseSouth);
        ourBaseX = (enemyBaseEast) ? (1) : (knownMapHeight -1);
        ourBaseY = (firstAgentNorth) ? (seekBaseDistance[firstAgent - 1] + 1) : (knownMapHeight - seekBaseDistance[firstAgent - 1] - 1);
        enemyBaseX = (ourBaseX == 1)?(knownMapHeight-1):(1);
        enemyBaseY = ourBaseY;
        System.out.println("Our base was calculated to be: (" + ourBaseX + ", " + ourBaseY + ")");
        map[ourBaseX-1][ourBaseY-1] = 'O';
        map[enemyBaseX -1][ourBaseY-1] = 'E';
        printMap();
    }

    public char[][] makeEmptyMap(){
        map = new char[knownMapHeight-1][knownMapHeight-1];
        for (int i = 0; i < knownMapHeight-1; i++) {
            for (int j = 0; j < knownMapHeight-1; j++) {
                map[i][j] = ' ';
            }
        }
        return map;
    }

    public int whichAgentFoundBaseFirst(){
        return (foundBaseFirst()) ? (agentNum) : ((agentNum == 1) ? (2) : (1));
    }

    public boolean foundBaseFirst(){
        return (agentNum == 1) ? ((!hasAgentIFoundBase[1]) ? (true) : (false)) : ((!hasAgentIFoundBase[0]) ? (true) : (false));
    }

    public void printMap (){
        for (int i = 0; i < knownMapHeight-1; i++) {
            for (int j = 0; j < knownMapHeight-1; j++) {
                System.out.print(map[j][i]);
            }
            System.out.println();
        }
    }

    public void setMySpawn(AgentEnvironment inEnvironment) {
        mySpawn.x = (enemyBaseWest) ? (knownMapHeight) : (1);
        mySpawn.y = (ourBaseSouth) ? (1) : (knownMapHeight);
        System.out.println("agent " + agentNum + " has spawn (" + mySpawn.x + ", " + mySpawn.y + ")");
    }

    public Boolean amIAtSpawn(AgentEnvironment inEnvironment){

        if((ourBaseWest == false) && (ourBaseEast == false)){
            if((ourBaseSouth == true) && (obstNorth == true)){
                if((enemyBaseWest == true) && (mySpawn.x == knownMapHeight) && (mySpawn.y == 1)){
                    System.out.println("agent" + agentNum + " has been respawned at (" + mySpawn.x + ", " + mySpawn.y + ")");
                    myPosition.x = mySpawn.x;
                    myPosition.y = mySpawn.y;
                    return true;
                }
                if((enemyBaseWest == false) && (mySpawn.x == 1) && (mySpawn.y == 1)){
                    System.out.println("agent" + agentNum + " has been respawned at (" + mySpawn.x + ", " + mySpawn.y + ")");
                    myPosition.x = mySpawn.x;
                    myPosition.y = mySpawn.y;
                    return true;
                }
            }else
            if((ourBaseNorth == true) && (obstSouth == true)){
                if((enemyBaseWest == true) && (mySpawn.x == knownMapHeight) && (mySpawn.y == knownMapHeight)){
                    System.out.println("agent" + agentNum + " has been respawned at (" + mySpawn.x + ", " + mySpawn.y + ")");
                    myPosition.x = mySpawn.x;
                    myPosition.y = mySpawn.y;
                    return true;
                }
                if((enemyBaseWest == false) && (mySpawn.x == 1) && (mySpawn.y == knownMapHeight)){
                    System.out.println("agent" + agentNum + " has been respawned at (" + mySpawn.x + ", " + mySpawn.y + ")");
                    myPosition.x = mySpawn.x;
                    myPosition.y = mySpawn.y;
                    return true;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
        return false;
    }

    public void queryEnvironment(AgentEnvironment inEnvironment){

        //do I currently have the flag
        hasFlag = inEnvironment.hasFlag();

        //direction of our base
        ourBaseWest = inEnvironment.isBaseWest(inEnvironment.OUR_TEAM, false);
        ourBaseEast = inEnvironment.isBaseEast(inEnvironment.OUR_TEAM, false);
        ourBaseSouth = inEnvironment.isBaseSouth(inEnvironment.OUR_TEAM, false);
        ourBaseNorth = inEnvironment.isBaseNorth(inEnvironment.OUR_TEAM, false);

        //immediate presence of our base
        ourBaseWestImmediate = inEnvironment.isBaseWest(inEnvironment.OUR_TEAM, true);
        ourBaseEastImmediate = inEnvironment.isBaseEast(inEnvironment.OUR_TEAM, true);
        ourBaseSouthImmediate = inEnvironment.isBaseSouth(inEnvironment.OUR_TEAM, true);
        ourBaseNorthImmediate = inEnvironment.isBaseNorth(inEnvironment.OUR_TEAM, true);

        //direction of enemy base
        enemyBaseEast = inEnvironment.isBaseEast(inEnvironment.ENEMY_TEAM, false);
        enemyBaseWest = inEnvironment.isBaseWest(inEnvironment.ENEMY_TEAM, false);
        enemyBaseNorth = inEnvironment.isBaseNorth(inEnvironment.ENEMY_TEAM, false);
        enemyBaseSouth = inEnvironment.isBaseSouth(inEnvironment.ENEMY_TEAM, false);

        //immediate presence of enemy base
        enemyBaseEastImmediate = inEnvironment.isBaseEast(inEnvironment.ENEMY_TEAM, true);
        enemyBaseWestImmediate = inEnvironment.isBaseWest(inEnvironment.ENEMY_TEAM, true);
        enemyBaseNorthImmediate = inEnvironment.isBaseNorth(inEnvironment.ENEMY_TEAM, true);
        enemyBaseSouthImmediate = inEnvironment.isBaseNorth(inEnvironment.ENEMY_TEAM, true);

        //presence of surrounding obstacles
        obstNorth = inEnvironment.isObstacleNorthImmediate();
        obstSouth = inEnvironment.isObstacleSouthImmediate();
        obstEast = inEnvironment.isObstacleEastImmediate();
        obstWest = inEnvironment.isObstacleWestImmediate();

        //immediate presence of enemy
        enemyNorthImmediate = inEnvironment.isAgentNorth(inEnvironment.ENEMY_TEAM, true);
        enemyEastImmediate = inEnvironment.isAgentEast(inEnvironment.ENEMY_TEAM, true);
        enemySouthImmediate = inEnvironment.isAgentSouth(inEnvironment.ENEMY_TEAM, true);
        enemyWestImmediate = inEnvironment.isAgentWest(inEnvironment.ENEMY_TEAM, true);

        //update the direction for all points of interest
        for(int i = 0; i < pointsOfInterest.size(); i++){
            if(pointsOfInterest.get(i).name == "ourBase"){
                if(ourBaseNorth && ourBaseEast){
                    pointsOfInterest.get(i).dir = direction.NORTHEAST;
                }else if(ourBaseEast && ourBaseSouth){
                    pointsOfInterest.get(i).dir = direction.SOUTHEAST;
                }else if(ourBaseWest && ourBaseSouth){
                    pointsOfInterest.get(i).dir = direction.SOUTHWEST;
                } else if(ourBaseWest && ourBaseNorth){
                    pointsOfInterest.get(i).dir = direction.NORTHWEST;
                }else if(ourBaseNorth){
                    pointsOfInterest.get(i).dir = direction.NORTH;
                }else if(ourBaseEast){
                    pointsOfInterest.get(i).dir = direction.EAST;
                }else if(ourBaseWest){
                    pointsOfInterest.get(i).dir = direction.WEST;
                } else if(ourBaseSouth){
                    pointsOfInterest.get(i).dir = direction.SOUTH;
                }
            }
            else if (pointsOfInterest.get(i).name == "enemyBase"){
                if(enemyBaseNorth && enemyBaseEast){
                    pointsOfInterest.get(i).dir = direction.NORTHEAST;
                }else if(enemyBaseEast && enemyBaseSouth){
                    pointsOfInterest.get(i).dir = direction.SOUTHEAST;
                }else if(enemyBaseWest && enemyBaseSouth){
                    pointsOfInterest.get(i).dir = direction.SOUTHWEST;
                } else if(enemyBaseWest && enemyBaseNorth){
                    pointsOfInterest.get(i).dir = direction.NORTHWEST;
                }else if(enemyBaseNorth){
                    pointsOfInterest.get(i).dir = direction.NORTH;
                }else if(enemyBaseEast){
                    pointsOfInterest.get(i).dir = direction.EAST;
                }else if(enemyBaseWest){
                    pointsOfInterest.get(i).dir = direction.WEST;
                } else if(enemyBaseSouth){
                    pointsOfInterest.get(i).dir = direction.SOUTH;
                }
            }
        }
    }

    String getDirectionName(direction dir){
        switch(dir){
            case NORTH:
                return "north";
            case NORTHEAST:
                return "northeast";
            case EAST:
                return "east";
            case SOUTHEAST:
                return "southeast";
            case SOUTH:
                return "south";
            case SOUTHWEST:
                return "southwest";
            case WEST:
                return "west";
            case NORTHWEST:
                return "northwest";
        }
        return "error";
    }

    void printPointsOfInterest() {
        System.out.print("agent " + agentNum + " ");
        for(int i = 0; i < pointsOfInterest.size(); i++){

            String name = pointsOfInterest.get(i).name;
            direction dir = pointsOfInterest.get(i).dir;
            System.out.print(name + ": " + getDirectionName(dir) + " ");
        }
        System.out.println();
    }
}

