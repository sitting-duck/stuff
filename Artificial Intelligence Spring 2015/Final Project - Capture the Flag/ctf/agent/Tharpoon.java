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

    private class Agent {
        public Integer number;
        public char name;
        public objective currentObjective;
        public Coordinate<Integer> spawn;
        public Coordinate<Integer> position;
        public ArrayList<Coordinate<Integer>> squaresTravelled;
        public ArrayList<Integer> movesMade;
        public boolean hasFlag;
        public boolean foundBase;

        public Agent() {
            number = -1;
            currentObjective = objective.INITIALIZE;
            spawn = new Coordinate<Integer>();
            position = new Coordinate<Integer>();
            squaresTravelled = new ArrayList<Coordinate<Integer>>();
            movesMade = new ArrayList<Integer>();
            hasFlag = false;
            foundBase = false;
        }
    }

    private class Place {
        String name;
        direction dir;
        Coordinate<Integer> position;

        Place(String name) {
            this.name = name;
            position = new Coordinate<Integer>();
        }
    }

    private class Coordinate<N> {
        public N x;
        public N y;

        public Coordinate() {
        }

        public Coordinate(N x, N y) {
            this.x = x;
            this.y = y;
        }

        public void set(N x, N y) {
            this.x = x;
            this.y = y;
        }

        public void set(Coordinate<N> otherCoordinate) {
            this.x = otherCoordinate.x;
            this.y = otherCoordinate.y;
        }

        public String toString() {
            return "(" + x + ", " + y + ")";
        }

        public boolean isEqualTo(Coordinate<N> otherCoordinate){
            return ((this.x == otherCoordinate.x) && (this.y == otherCoordinate.y));
        }
    }

    //Agents
    private final static int MAX_NUM_AGENTS = 2;
    private static ArrayList<Agent> agents = new ArrayList<Agent>();
    private Agent me;
    private Agent otherAgent;

    private enum objective {INITIALIZE, SEEK_ENEMY_BASE, SEEK_OUR_BASE, RETRIEVE_FRIENDLY_FLAG}


    //Map
    private static char[][] map;
    private int mapHeight = 10;         //it is known that mapHeight == mapLength
    Place ourBase;
    Place enemyBase;
    ArrayList<Place> pointsOfInterest = new ArrayList<Place>();

    private enum direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST, DONOTHING}


    //Environment Variables
    private boolean obstNorth;
    private boolean obstSouth;
    private boolean obstEast;
    private boolean obstWest;
    private boolean blockedNorthEast;
    private boolean blockedSouthEast;
    private boolean blockedNorthWest;
    private boolean blockedSouthWest;
    private boolean blockedNorthEastSouth;
    private boolean blockedEastSouthWest;
    private boolean blockedSouthWestNorth;
    private boolean blockedWestNorthEast;
    private boolean blockedEveryDirection;

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

    private boolean enemyNorthImmediate;
    private boolean enemyEastImmediate;
    private boolean enemySouthImmediate;
    private boolean enemyWestImmediate;

    private int moveNorth = AgentAction.MOVE_NORTH;
    private int moveEast = AgentAction.MOVE_EAST;
    private int moveSouth = AgentAction.MOVE_SOUTH;
    private int moveWest = AgentAction.MOVE_WEST;
    private int doNothing = AgentAction.DO_NOTHING;
    private int plantMine = AgentAction.PLANT_HYPERDEADLY_PROXIMITY_MINE;


    public Tharpoon() {

        //Agent
        if (agents.size() == MAX_NUM_AGENTS) {
            agents.clear();
        }
        me = new Agent();
        agents.add(me);
        me.number = agents.size() - 1;
        me.name = (char) ('a' + me.number);
        System.out.println("added agent " + me.name + me.number);

        //Map
        makeEmptyMap();
        ourBase = new Place("ourBase");
        enemyBase = new Place("enemyBase");
        pointsOfInterest.add(ourBase);
        pointsOfInterest.add(enemyBase);
    }

    public int getMove(AgentEnvironment inEnvironment) {

        int whatToDo = doNothing;

        //init
        queryEnvironment(inEnvironment);

        if (me.currentObjective == objective.INITIALIZE) {
            determineMySpawnAndInitialPosition();
            if (me.number == agents.size() - 1) {
                determineBasePositions();
            }
            me.currentObjective = objective.SEEK_ENEMY_BASE;
        }

        amIAtSpawn();
        addSurroundingObstaclesToMap(inEnvironment);
        if (me.hasFlag) {
            me.currentObjective = objective.SEEK_OUR_BASE;
        }else{
            me.currentObjective = objective.SEEK_ENEMY_BASE;
        }

        switch (me.currentObjective) {
            case SEEK_ENEMY_BASE:
                whatToDo = seek(enemyBase);
                break;
            case SEEK_OUR_BASE:
                whatToDo = seek(ourBase);
                break;
        }

        //print only after every complete move (ie, both agents have moved)
        if (me.number == 1) {
            printMap();
        }

        return whatToDo;

    }

    public int seek(Place place) {

        int whatToDo = doNothing;

        if (blockedInThreeDirections()) {
            whatToDo = getAgentActionFromDirection(getOnlyFreeDirection());
            return whatToDo;
        }

        direction directionToGo = place.dir;

        if(oscillatingMoveCheck()){
            System.out.println("omc = " + oscillatingMoveCheck());
            directionToGo = getDirectionFromAgentAction(getLastMove());
        }

        switch (directionToGo) {
            case NORTH:
                whatToDo = preferInOrder(direction.NORTH, direction.EAST, direction.WEST, direction.SOUTH);
                break;
            case NORTHEAST:
                whatToDo = preferInOrder(direction.EAST, direction.NORTH, direction.SOUTH, direction.WEST);
                break;
            case NORTHWEST:
                whatToDo = preferInOrder(direction.WEST, direction.NORTH, direction.SOUTH, direction.EAST);
                break;
            case SOUTH:
                whatToDo = preferInOrder(direction.SOUTH, direction.EAST, direction.WEST, direction.NORTH);
                break;
            case SOUTHEAST:
                whatToDo = preferInOrder(direction.EAST, direction.SOUTH, direction.NORTH, direction.WEST);
                break;
            case SOUTHWEST:
                whatToDo = preferInOrder(direction.WEST, direction.SOUTH, direction.NORTH, direction.EAST);
                break;
            case EAST:
                whatToDo = preferInOrder(direction.EAST, direction.NORTH, direction.SOUTH, direction.WEST);
                break;
            case WEST:
                whatToDo = preferInOrder(direction.WEST, direction.NORTH, direction.SOUTH, direction.EAST);
                break;
        }

        return whatToDo;
    }

    //MAP FUNCTIONS//MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS


    public boolean oscillatingMoveCheck(){
        if(me.squaresTravelled.size() == 1){
            return false;
        }else{
            return (getXPositionsBack(2).isEqualTo(me.position));
        }

    }

    public Coordinate<Integer> getLastPosition(){
        return me.squaresTravelled.get(me.squaresTravelled.size() - 1);
    }

    public Coordinate<Integer> getXPositionsBack(Integer x){
        return me.squaresTravelled.get(me.squaresTravelled.size() - x);
    }

    public int getLastMove(){
        return me.movesMade.get(me.movesMade.size() - 1);
    }

    public int getXMovesBack(Integer x){
        return me.movesMade.get(me.movesMade.size() - x);
    }

    public direction getOppositeDirection(direction dir){
        direction opposite = direction.DONOTHING;
        switch(dir){
            case NORTH:
                opposite = direction.SOUTH;
                break;
            case NORTHEAST:
                opposite = direction.SOUTHWEST;
                break;
            case EAST:
                opposite = direction.WEST;
                break;
            case SOUTHEAST:
                opposite = direction.NORTHWEST;
                break;
            case SOUTH:
                opposite = direction.NORTH;
                break;
            case SOUTHWEST:
                opposite = direction.NORTHEAST;
                break;
            case WEST:
                opposite = direction.EAST;
                break;
            case NORTHWEST:
                opposite = direction.SOUTHEAST;
                break;
        }
        return opposite;
    }

    public int preferSameDirectionAsPreviousMove(){
        if(getLastMove() == moveNorth && okayToGoNorth()){
            return moveNorth();
        }else if(getLastMove() == moveSouth && okayToGoSouth()){
            return moveSouth();
        }else if(getLastMove() == moveEast && okayToGoEast()){
            return moveEast();
        }else if(getLastMove() == moveWest && okayToGoWest()){
            return moveWest();
        }else{
            return doNothing;
        }
    }

    public int preferOppositeDirectionOfPreviousMove(){
        if(getLastMove() == moveNorth && okayToGoSouth()){
            return moveSouth();
        }else if(getLastMove() == moveSouth && okayToGoNorth()){
            return moveNorth();
        }else if(getLastMove() == moveEast && okayToGoWest()){
            return moveWest();
        }else if(getLastMove() == moveWest && okayToGoEast()){
            return moveEast();
        }else{
            return doNothing;
        }
    }

    public int moveNorth(){
        Coordinate<Integer> newPosition = new Coordinate<Integer>(me.position.x, me.position.y - 1);
        changeMyPosition(me.position, newPosition);
        me.movesMade.add(moveNorth);
        return moveNorth;
    }

    public int moveEast(){
        Coordinate<Integer> newPosition = new Coordinate<Integer>(me.position.x + 1, me.position.y);
        changeMyPosition(me.position, newPosition);
        me.movesMade.add(moveEast);
        return moveEast;
    }

    public int moveSouth(){
        Coordinate<Integer> newPosition = new Coordinate<Integer>(me.position.x, me.position.y + 1);
        changeMyPosition(me.position, newPosition);
        me.movesMade.add(moveSouth);
        return moveSouth;
    }

    public int moveWest(){
        Coordinate<Integer> newPosition = new Coordinate<Integer>(me.position.x - 1, me.position.y);
        changeMyPosition(me.position, newPosition);
        me.movesMade.add(moveWest);
        return moveWest;
    }

    public int preferInOrder(direction firstDirection, direction secondDirection, direction thirdDirection, direction fourthDirection){
        int whatToDo = doNothing;
        if(okayToGo(firstDirection)){
            return move(firstDirection);
        }else if(okayToGo(secondDirection)){
            return move(secondDirection);
        }else if(okayToGo(thirdDirection)){
            return move(thirdDirection);
        }else if(okayToGo(fourthDirection)){
            return move(fourthDirection);
        }else{
            whatToDo = doNothing;
        }
        return whatToDo;
    }

    boolean okayToGo(direction dir){
        switch(dir){
            case NORTH:
                return okayToGoNorth();
            case EAST:
                return okayToGoEast();
            case SOUTH:
                return okayToGoSouth();
            case WEST:
                return okayToGoWest();
        }
        return false;
    }

    int move(direction dir){
        switch(dir){
            case NORTH:
                return moveNorth();
            case EAST:
                return moveEast();
            case SOUTH:
                return moveSouth();
            case WEST:
                return moveWest();
        }
        return doNothing;
    }

    public void addSurroundingObstaclesToMap(AgentEnvironment inEnvironment) {

        //presence of surrounding obstacles
        if(me.position.y == 0){
            obstNorth = inEnvironment.isObstacleNorthImmediate();
        }else{
            obstNorth = (inEnvironment.isObstacleNorthImmediate() || (map[me.position.x][me.position.y - 1] == 'X'));
        }

        if(me.position.y == mapHeight - 1){
            obstSouth = inEnvironment.isObstacleSouthImmediate();
        }else{
            obstSouth = (inEnvironment.isObstacleSouthImmediate() || (map[me.position.x][me.position.y + 1] == 'X'));
        }

        if(me.position.x == mapHeight -1){
            obstEast  = inEnvironment.isObstacleEastImmediate();
        }else{
            obstEast  = (inEnvironment.isObstacleEastImmediate() || (map[me.position.x + 1][me.position.y] == 'X'));
        }

        if(me.position.x == 0){
            obstWest  = inEnvironment.isObstacleWestImmediate();
        }else{
            obstWest  = (inEnvironment.isObstacleWestImmediate() || (map[me.position.x - 1][me.position.y] == 'X'));
        }

        blockedNorthEastSouth = (obstNorth && obstEast && obstSouth);
        blockedEastSouthWest = (obstEast && obstSouth && obstWest);
        blockedSouthWestNorth = (obstSouth && obstWest && obstNorth);
        blockedWestNorthEast = (obstWest && obstNorth && obstEast);
        blockedEveryDirection = (obstWest && obstNorth && obstEast && obstSouth);

        if (obstNorth && me.position.y != 0) {
            map[me.position.x][me.position.y - 1] = 'X';
        }
        if (obstEast && me.position.x != mapHeight - 1) {
            map[me.position.x + 1][me.position.y] = 'X';
        }
        if (obstSouth && me.position.y != mapHeight - 1) {
            map[me.position.x][me.position.y + 1] = 'X';
        }
        if (obstWest && me.position.x != 0) {
            map[me.position.x - 1][me.position.y] = 'X';
        }

        //if(blockedInThreeDirections()){map[me.position.x][me.position.y] = 'X';}
    }

    public void determineMySpawnAndInitialPosition() {

        if (enemyBaseEast && ourBaseSouth) {
            me.spawn.set(0, 0);
        } else if (enemyBaseEast && ourBaseNorth) {
            me.spawn.set(0, mapHeight - 1);
        } else if (enemyBaseWest && ourBaseNorth) {
            me.spawn.set(mapHeight - 1, mapHeight - 1);
        } else if (enemyBaseWest && ourBaseSouth) {
            me.spawn.set(mapHeight - 1, 0);
        }
        me.position.set(me.spawn);
        //System.out.println("agent " + me.number + " init: " + me.position.toString());
    }

    public Boolean amIAtSpawn() {

        if ((ourBaseWest == false) && (ourBaseEast == false)) {
            if ((ourBaseSouth == true) && (obstNorth == true)) {
                if ((enemyBaseWest == true) && (me.spawn.x == mapHeight - 1) && (me.spawn.y == 0)) {
                    System.out.println("agent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                    changeMyPosition(me.position, me.spawn);
                    return true;
                }
                if ((enemyBaseWest == false) && (me.spawn.x == 0) && (me.spawn.y == 0)) {
                    System.out.println("agent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                    changeMyPosition(me.position, me.spawn);
                    return true;
                }
            } else if ((ourBaseNorth == true) && (obstSouth == true)) {
                if ((enemyBaseWest == true) && (me.spawn.x == mapHeight - 1) && (me.spawn.y == mapHeight - 1)) {
                    System.out.println("agent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                    changeMyPosition(me.position, me.spawn);
                    return true;
                }
                if ((enemyBaseWest == false) && (me.spawn.x == 0) && (me.spawn.y == mapHeight - 1)) {
                    System.out.println("agent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                    changeMyPosition(me.position, me.spawn);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
        return false;
    }

    public void determineBasePositions() {
        if (enemyBaseWest) {
            ourBase.position.set(9, 5);
            enemyBase.position.set(0, 5);
        } else if (enemyBaseEast) {
            ourBase.position.set(0, 5);
            enemyBase.position.set(9, 5);
        }
        System.out.println("enemy base: " + enemyBase.position.toString());
        System.out.println("ourBase: " + ourBase.position.toString());
    }

    public void setMapSquare(Coordinate<Integer> pos, char c) {
        map[pos.x][pos.y] = c;
    }

    public void moveMeOnMap(Coordinate<Integer> source, Coordinate<Integer> destination) {
        if(blockedInThreeDirections()){
            setMapSquare(source, 'X');
        }else {
            setMapSquare(source, ' ');
        }
        setMapSquare(destination, me.name);
    }

    public void changeMyPosition(Coordinate<Integer> source, Coordinate<Integer> destination) {
        me.squaresTravelled.add(source);
        moveMeOnMap(source, destination);
        me.position.set(destination);
    }

    public char[][] makeEmptyMap() {
        map = new char[mapHeight][mapHeight];
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapHeight; j++) {
                map[i][j] = '.';
            }
        }
        return map;
    }

    public void printMap() {

        map[ourBase.position.x][ourBase.position.y] = 'O';
        map[enemyBase.position.x][enemyBase.position.y] = 'E';

        for (int i = 0; i < agents.size(); i++) {
            map[agents.get(i).position.x][agents.get(i).position.y] = agents.get(i).name;
        }

        System.out.println("----------");
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapHeight; j++) {
                System.out.print(map[j][i]);
            }
            System.out.println();
        }
        System.out.println("----------");
    }

    //ENVIRONMENT FUNCTIONS//ENVIRONMENT FUNCTIONS //ENVIRONMENT FUNCTIONS //ENVIRONMENT FUNCTIONS //ENVIRONMENT FUNCTIONS //ENVIRONMENT FUNCTIONS

    public boolean okayToGoNorth() {
        return ((me.hasFlag && enemyNorthImmediate) || obstNorth || ourBaseNorthImmediate) ? (false) : (true);
    }

    public boolean okayToGoEast() {
        return ((me.hasFlag && enemyEastImmediate) || obstEast || ourBaseEastImmediate) ? (false) : (true);
    }

    public boolean okayToGoWest() {
        return ((me.hasFlag && enemyWestImmediate) || obstWest || ourBaseWestImmediate) ? (false) : (true);
    }

    public boolean okayToGoSouth() {
        return ((me.hasFlag && enemySouthImmediate) || obstSouth || ourBaseSouthImmediate) ? (false) : (true);
    }

    public void queryEnvironment(AgentEnvironment inEnvironment) {

        //do I currently have the flag
        me.hasFlag = inEnvironment.hasFlag();

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
        obstEast  = inEnvironment.isObstacleEastImmediate();
        obstWest  = inEnvironment.isObstacleWestImmediate();

        blockedNorthEast = (obstNorth && obstEast);
        blockedSouthEast = (obstSouth && obstEast);
        blockedNorthWest = (obstNorth && obstWest);
        blockedSouthWest = (obstSouth && obstWest);

        //immediate presence of enemy
        enemyNorthImmediate = inEnvironment.isAgentNorth(inEnvironment.ENEMY_TEAM, true);
        enemyEastImmediate = inEnvironment.isAgentEast(inEnvironment.ENEMY_TEAM, true);
        enemySouthImmediate = inEnvironment.isAgentSouth(inEnvironment.ENEMY_TEAM, true);
        enemyWestImmediate = inEnvironment.isAgentWest(inEnvironment.ENEMY_TEAM, true);

        //update the direction for all points of interest
        for (int i = 0; i < pointsOfInterest.size(); i++) {
            if (pointsOfInterest.get(i).name == "ourBase") {
                if (ourBaseNorth && ourBaseEast) {
                    pointsOfInterest.get(i).dir = direction.NORTHEAST;
                } else if (ourBaseEast && ourBaseSouth) {
                    pointsOfInterest.get(i).dir = direction.SOUTHEAST;
                } else if (ourBaseWest && ourBaseSouth) {
                    pointsOfInterest.get(i).dir = direction.SOUTHWEST;
                } else if (ourBaseWest && ourBaseNorth) {
                    pointsOfInterest.get(i).dir = direction.NORTHWEST;
                } else if (ourBaseNorth) {
                    pointsOfInterest.get(i).dir = direction.NORTH;
                } else if (ourBaseEast) {
                    pointsOfInterest.get(i).dir = direction.EAST;
                } else if (ourBaseWest) {
                    pointsOfInterest.get(i).dir = direction.WEST;
                } else if (ourBaseSouth) {
                    pointsOfInterest.get(i).dir = direction.SOUTH;
                }
            } else if (pointsOfInterest.get(i).name == "enemyBase") {
                if (enemyBaseNorth && enemyBaseEast) {
                    pointsOfInterest.get(i).dir = direction.NORTHEAST;
                } else if (enemyBaseEast && enemyBaseSouth) {
                    pointsOfInterest.get(i).dir = direction.SOUTHEAST;
                } else if (enemyBaseWest && enemyBaseSouth) {
                    pointsOfInterest.get(i).dir = direction.SOUTHWEST;
                } else if (enemyBaseWest && enemyBaseNorth) {
                    pointsOfInterest.get(i).dir = direction.NORTHWEST;
                } else if (enemyBaseNorth) {
                    pointsOfInterest.get(i).dir = direction.NORTH;
                } else if (enemyBaseEast) {
                    pointsOfInterest.get(i).dir = direction.EAST;
                } else if (enemyBaseWest) {
                    pointsOfInterest.get(i).dir = direction.WEST;
                } else if (enemyBaseSouth) {
                    pointsOfInterest.get(i).dir = direction.SOUTH;
                }
            }
        }
    }

    public boolean blockedInThreeDirections() {
        return (blockedNorthEastSouth || blockedEastSouthWest || blockedSouthWestNorth || blockedWestNorthEast);
    }

    public direction getOnlyFreeDirection() {
        direction freeDirection = direction.EAST;
        if (blockedNorthEastSouth) {
            freeDirection = direction.WEST;
        } else if (blockedEastSouthWest) {
            freeDirection = direction.NORTH;
        } else if (blockedSouthWestNorth) {
            freeDirection = direction.EAST;
        } else if (blockedWestNorthEast) {
            freeDirection = direction.SOUTH;
        }
        return freeDirection;
    }

    //STRING CONVERSION FUNCTIONS //STRING CONVERSION FUNCTIONS //STRING CONVERSION FUNCTIONS //STRING CONVERSION FUNCTIONS
    public String getNameFromAgentAction(int action) {
        String name = "does nothing";

        switch (action) {
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

    public String getDirectionName(direction dir) {
        switch (dir) {
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

    public int getAgentActionFromDirection(direction dir) {
        int action = doNothing;

        switch (dir) {
            case NORTH:
                action = moveNorth;
                moveNorth();
                break;
            case EAST:
            case NORTHEAST:
            case SOUTHEAST:
                action = moveEast;
                moveEast();
                break;
            case WEST:
            case NORTHWEST:
            case SOUTHWEST:
                action = moveWest;
                moveWest();
                break;
            case SOUTH:
                action = moveSouth;
                moveSouth();
                break;
        }
        return action;
    }

    public direction getDirectionFromAgentAction(int lastAction){
        direction dir = direction.DONOTHING;
        if(lastAction == moveNorth){
            dir = direction.NORTH;
        }else if(lastAction == moveEast){
            dir = direction.EAST;
        }else if(lastAction == moveWest){
            dir = direction.WEST;
        }else{
            dir = direction.SOUTH;
        }
        return dir;
    }
}