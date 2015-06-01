package ctf.agent;

import java.util.Random;
import java.lang.Integer;
import java.lang.System;
import java.util.ArrayList;
import java.lang.Math;
import ctf.common.AgentAction;
import ctf.common.AgentEnvironment;
import ctf.agent.Agent;
import ctf.common.AgentAction;

public class Tharpoon4 extends Agent {

    private class TharpoonAgent {
        public Integer number;
        public char name;
        public ArrayList<Objective> objectives;
        public Coordinate spawn;
        public Coordinate position;
        public ArrayList<Coordinate> squaresTravelled;
        public ArrayList<Integer> movesMade;
        public boolean hasFlag;

        public TharpoonAgent() {
            number = -1;
            objectives = new ArrayList<Objective>();
            pushObjective(Objective.INITIALIZE);
            spawn = new Coordinate();
            position = new Coordinate();
            squaresTravelled = new ArrayList<Coordinate>();
            movesMade = new ArrayList<Integer>();
            hasFlag = false;
        }

        public Objective getCurrentObjective() {
            return objectives.get(objectives.size() - 1);
        }

        public Objective getXObjectivesBack(int x) {
            return objectives.get((objectives.size() - 1) - x);
        }

        public TharpoonAgent setNewCurrentObjective(Objective newObjective) {
            popObjective();
            pushObjective(newObjective);
            return this;
        }

        public TharpoonAgent pushObjective(Objective newObjective) {
            objectives.add(newObjective);
            return this;
        }

        public TharpoonAgent popObjective() {
            objectives.remove(objectives.size() - 1);
            return this;
        }

        public Coordinate oneNorth() {
            return position.oneNorth();
        }

        public Coordinate oneEast() {
            return position.oneEast();
        }

        public Coordinate oneSouth() {
            return position.oneSouth();
        }

        public Coordinate oneWest() {
            return position.oneWest();
        }
    }

    private class Place {
        String name;
        Direction dir;
        Coordinate position;

        Place(String name) {
            this.name = name;
            position = new Coordinate();
        }
    }

    private class Coordinate {
        public Integer x;
        public Integer y;

        public Coordinate() {
        }

        public Coordinate(Integer x, Integer y) {
            this.x = x;
            this.y = y;
        }

        public Coordinate(Coordinate otherCoordinate) {
            this.x = otherCoordinate.x;
            this.y = otherCoordinate.y;
        }

        public void set(Integer x, Integer y) {
            this.x = x;
            this.y = y;
        }

        public void set(Coordinate otherCoordinate) {
            this.x = otherCoordinate.x;
            this.y = otherCoordinate.y;
        }

        public String toString() {
            return "(" + x + ", " + y + ")";
        }

        public boolean isEqualTo(Coordinate otherCoordinate) {
            return ((this.x == otherCoordinate.x) && (this.y == otherCoordinate.y));
        }

        public Coordinate oneNorth() {
            return new Coordinate(this.x, this.y - 1);
        }

        public Coordinate oneSouth() {
            return new Coordinate(x, y + 1);
        }

        public Coordinate oneEast() {
            return new Coordinate(x + 1, y);
        }

        public Coordinate oneWest() {
            return new Coordinate(x - 1, y);
        }
    }

    public class GlobalMap {
        int mapHeight;
        int mapWidth;
        char[][] map;
        ArrayList<Coordinate> possibleMines;

        public GlobalMap(int w, int h) {
            mapWidth = w;
            mapHeight = h;
            map = new char[w][h];
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    map[i][j] = '.';
                }
            }
        }

        public GlobalMap set(Coordinate pos, char c) {
            map[pos.x][pos.y] = c;
            return this;
        }

        public char get(Coordinate pos) {
            return get(pos.x, pos.y);
        }

        public char get(int x, int y) {
            return map[x][y];
        }

        public GlobalMap print(TharpoonEnvironment env, TharpoonAgent me) {
            update(env, me);

            if (me.number != 1) {
                return this;
            }

            System.out.println("----------");
            for (int i = 0; i < mapWidth; i++) {
                for (int j = 0; j < mapHeight; j++) {
                    System.out.print(map[j][i]);
                }
                System.out.println();
            }
            System.out.println("----------");
            return this;
        }

        public void update(TharpoonEnvironment env, TharpoonAgent me) {

            addSurroundingObstaclesToMap(env, me);


            //mark my old position as blank if it is not an X
            //if (me.squaresTravelled.size() > 1) {
            //    Coordinate oldPosition = me.squaresTravelled.get(me.squaresTravelled.size() - 1);
            //    if (get(oldPosition) != 'X') {
            //        set(oldPosition, '.');
            //    }
            //}

            //if I am block on all sides but one, mark this square as an obst, else, mark that I am here
            char myPosChar = (obstInThreeDirections(env)) ? ('X') : (me.name);
            set(me.position, myPosChar);

            set(me.position, me.name);


            //add our base and enemy base to the map
            set(ourBase.position, 'O');
            set(enemyBase.position, 'E');

        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                        OBSTACLE BOOKKEEPING
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        public boolean obstInThreeDirections(TharpoonEnvironment env) {
            return (env.obstNorthEastSouth || env.obstEastSouthWest || env.obstSouthWestNorth || env.obstWestNorthEast);
        }

        public void updateObstaclePresenceForFoundObstacles(TharpoonEnvironment env, TharpoonAgent me) {
            //presence of surrounding obstacles
            if (me.position.y != 0) {
                env.obstNorth = (env.environmentHandle.isObstacleNorthImmediate() || (map[me.position.x][me.position.y - 1] == 'X'));
            } else {
                env.obstNorth = env.environmentHandle.isObstacleNorthImmediate();
            }

            if (me.position.y != mapHeight - 1) {
                env.obstSouth = (env.environmentHandle.isObstacleSouthImmediate() || (map[me.position.x][me.position.y + 1] == 'X'));
            } else {
                env.obstSouth = env.environmentHandle.isObstacleSouthImmediate();
            }

            if (me.position.x != mapHeight - 1) {
                env.obstEast = (env.environmentHandle.isObstacleEastImmediate() || (map[me.position.x + 1][me.position.y] == 'X'));
            } else {
                env.obstEast = env.environmentHandle.isObstacleEastImmediate();
            }

            if (me.position.x != 0) {
                env.obstWest = (env.environmentHandle.isObstacleWestImmediate() || (map[me.position.x - 1][me.position.y] == 'X'));
            } else {
                env.obstWest = env.environmentHandle.isObstacleWestImmediate();
            }

            env.obstNorthEastSouth = (env.obstNorth && env.obstEast && env.obstSouth);
            env.obstEastSouthWest = (env.obstEast && env.obstSouth && env.obstWest);
            env.obstSouthWestNorth = (env.obstSouth && env.obstWest && env.obstNorth);
            env.obstWestNorthEast = (env.obstWest && env.obstNorth && env.obstEast);
            env.obstEveryDirection = (env.obstWest && env.obstNorth && env.obstEast && env.obstSouth);
        }

        public void addSurroundingObstaclesToMap(TharpoonEnvironment env, TharpoonAgent me) {

            queryEnvironment(env.environmentHandle);
            updateObstaclePresenceForFoundObstacles(env, me);

            if (env.obstNorth && (me.position.y != 0)) {
                set(me.position.oneNorth(), 'X');
            }
            if (env.obstEast && (me.position.x != mapHeight - 1)) {
                set(me.position.oneEast(), 'X');
            }
            if (env.obstSouth && (me.position.y != mapHeight - 1)) {
                set(me.position.oneSouth(), 'X');
            }
            if (env.obstWest && (me.position.x != 0)) {
                set(me.position.oneWest(), 'X');
            }
        }

        public GlobalMap changeTharpoonAgentPosition() {
            return this;
        }

        public void determineMySpawnAndInitialPosition(TharpoonEnvironment env, TharpoonAgent me) {

            if (env.enemyBaseEast && env.ourBaseSouth) {
                me.spawn.set(0, 0);
            } else if (env.enemyBaseEast && env.ourBaseNorth) {
                me.spawn.set(0, mapHeight - 1);
            } else if (env.enemyBaseWest && env.ourBaseNorth) {
                me.spawn.set(mapHeight - 1, mapHeight - 1);
            } else if (env.enemyBaseWest && env.ourBaseSouth) {
                me.spawn.set(mapHeight - 1, 0);
            }
            me.position.set(me.spawn);
            //System.out.println("TharpoonAgent " + me.number + " init: " + me.position.toString());
        }

        public Boolean amIAtSpawn(TharpoonEnvironment env, GlobalMap map) {

            if ((env.ourBaseWest == false) && (env.ourBaseEast == false)) {
                if ((env.ourBaseSouth == true) && (env.obstNorth == true)) {
                    if ((env.enemyBaseWest == true) && (me.spawn.x == mapHeight - 1) && (me.spawn.y == 0)) {
                        System.out.println("TharpoonAgent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                        changeMyPosition(env, me, me.position, me.spawn);
                        return true;
                    }
                    if ((env.enemyBaseWest == false) && (me.spawn.x == 0) && (me.spawn.y == 0)) {
                        System.out.println("TharpoonAgent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                        changeMyPosition(env, me, me.position, me.spawn);
                        return true;
                    }
                } else if ((env.ourBaseNorth == true) && (env.obstSouth == true)) {
                    if ((env.enemyBaseWest == true) && (me.spawn.x == mapHeight - 1) && (me.spawn.y == mapHeight - 1)) {
                        System.out.println("TharpoonAgent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                        changeMyPosition(env, me, me.position, me.spawn);
                        return true;
                    }
                    if ((env.enemyBaseWest == false) && (me.spawn.x == 0) && (me.spawn.y == mapHeight - 1)) {
                        System.out.println("TharpoonAgent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                        changeMyPosition(env, me, me.position, me.spawn);
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

        public void determineBasePositions(TharpoonEnvironment env) {
            if (env.enemyBaseWest) {
                ourBase.position.set(9, 5);
                enemyBase.position.set(0, 5);
            } else if (env.enemyBaseEast) {
                ourBase.position.set(0, 5);
                enemyBase.position.set(9, 5);
            }
            System.out.println("enemy base: " + enemyBase.position.toString());
            System.out.println("ourBase: " + ourBase.position.toString());
        }

        public void changeMyPosition(TharpoonEnvironment env, TharpoonAgent me, Coordinate source, Coordinate destination) {
            me.squaresTravelled.add(new Coordinate(destination));
            moveMeOnMap(env, source, destination, me);
            me.position.set(destination);
        }

        public void moveMeOnMap(TharpoonEnvironment env, Coordinate source, Coordinate destination, TharpoonAgent me) {
            if(obstInThreeDirections(env)){
                set(source, 'X');
            }else {
                set(source, ' ');
            }
            set(destination, me.name);
        }
    }

    public class TharpoonEnvironment{

        AgentEnvironment environmentHandle;

        public TharpoonEnvironment(){}

        //TharpoonEnvironment Variables
        private boolean obstNorth;
        private boolean obstSouth;
        private boolean obstEast;
        private boolean obstWest;
        private boolean obstNorthEast;
        private boolean obstSouthEast;
        private boolean obstNorthWest;
        private boolean obstSouthWest;
        private boolean obstNorthEastSouth;
        private boolean obstEastSouthWest;
        private boolean obstSouthWestNorth;
        private boolean obstWestNorthEast;
        private boolean obstEveryDirection;

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

        private boolean enemyHasOurFlag;

        private boolean friendlyNorthImmediate;
        private boolean friendlyEastImmediate;
        private boolean friendlySouthImmediate;
        private boolean friendlyWestImmediate;
    }

    //TharpoonAgents
    private final static int MAX_NUM_TharpoonAgentS = 2;
    private static ArrayList<TharpoonAgent> TharpoonAgents = new ArrayList<TharpoonAgent>();
    private TharpoonAgent me;
    private TharpoonAgent otherTharpoonAgent;

    private enum Objective {INITIALIZE, DETERMINE_OBJECTIVE, SEEK_ENEMY_BASE, SEEK_OUR_BASE, RETRIEVE_FRIENDLY_FLAG, DEFEND_OUR_BASE, GO_AROUND_OBSTACLE}


    //Map
    GlobalMap map;
    Place ourBase;
    Place enemyBase;
    Place defenseWallCenter;
    ArrayList<Place> pointsOfInterest = new ArrayList<Place>();

    //TharpoonEnvironment
    TharpoonEnvironment env;

    private enum Direction {NORTH, EAST, SOUTH, WEST, SOUTHWEST, SOUTHEAST, NORTHEAST, NORTHWEST, DONOTHING}

    //Strategy
    boolean oneDefenderOneOffender = false;

    private int moveNorth = AgentAction.MOVE_NORTH;
    private int moveEast = AgentAction.MOVE_EAST;
    private int moveSouth = AgentAction.MOVE_SOUTH;
    private int moveWest = AgentAction.MOVE_WEST;
    private int doNothing = AgentAction.DO_NOTHING;
    private int plantMine = AgentAction.PLANT_HYPERDEADLY_PROXIMITY_MINE;

    Random rand;


    public Tharpoon4() {

        //TharpoonAgent
        if (TharpoonAgents.size() == MAX_NUM_TharpoonAgentS) {
            TharpoonAgents.clear();
        }
        me = new TharpoonAgent();
        TharpoonAgents.add(me);
        me.number = TharpoonAgents.size() - 1;
        me.name = (char) ('a' + me.number);
        System.out.println("added TharpoonAgent " + me.name + me.number);

        //Map
        map = new GlobalMap(10, 10);
        ourBase = new Place("ourBase");
        enemyBase = new Place("enemyBase");
        defenseWallCenter = new Place("defenseWallCenter");
        pointsOfInterest.add(ourBase);
        pointsOfInterest.add(enemyBase);
        pointsOfInterest.add(defenseWallCenter);

        //TharpoonEnvironment
        env = new TharpoonEnvironment();
    }

    public int getMove(AgentEnvironment inEnvironment) {

        int whatToDo = doNothing;

       initializeTharpoonEnvironment(inEnvironment);

        map.amIAtSpawn(env, map);
        map.addSurroundingObstaclesToMap(env, me);

        switch (me.getCurrentObjective()) {
            case DETERMINE_OBJECTIVE:
                determineObjective();
                break;
            case SEEK_ENEMY_BASE:
                whatToDo = seek(enemyBase);
                break;
            case SEEK_OUR_BASE:
                whatToDo = seek(ourBase);
                break;
            case DEFEND_OUR_BASE:
                //whatToDo = defend(ourBase);
                break;
        }

        //print only after every complete move (ie, both TharpoonAgents have moved)
        map.print(env, me);

        return whatToDo;

    }

    public void initializeTharpoonEnvironment(AgentEnvironment inEnvironment) {
        //init
        queryEnvironment(inEnvironment);

        //some initilizations before we start seeking
        if (me.getCurrentObjective() == Objective.INITIALIZE) {
            map.determineMySpawnAndInitialPosition(env, me);
            map.determineBasePositions(env);

            me.setNewCurrentObjective(Objective.DETERMINE_OBJECTIVE);
        }
    }

    public void determineObjective(){
        if(me.hasFlag){
            me.pushObjective(Objective.SEEK_OUR_BASE);
        }else if(!me.hasFlag){
            me.pushObjective(Objective.SEEK_ENEMY_BASE);
        }
    }

    public int seek(Place place) {

        int whatToDo = doNothing;

        if (map.obstInThreeDirections(env)) {
            whatToDo = getTharpoonAgentActionFromDirection(getOnlyFreeDirection());
            return whatToDo;
        }

        Direction DirectionToGo = place.dir;

        if(oscillatingMoveCheck()){
            DirectionToGo = getDirectionFromTharpoonAgentAction(getXMovesBack(2));
        }

        //int tagEnemyWithOurFlag = checkForSurroundingEnemyTharpoonAgentsWithOurFlag();
        //if(tagEnemyWithOurFlag != doNothing){
        //    return tagEnemyWithOurFlag;
        //}

        //if(smallCircleCheck()){
        //    return goRandomOpenDirection();
        //}

        switch (DirectionToGo) {
            case NORTH:
                if (okayToGoNorth()) {
                    whatToDo = moveNorth();
                    //}else if(me.currentObjective == Objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(Direction.NORTH, Direction.EAST, Direction.WEST, Direction.SOUTH);
                }
                break;
            case NORTHEAST:
                if(okayToGoNorth() && okayToGoEast()){
                    //whatToDo = preferInOrder(Direction.EAST, Direction.NORTH);
                    whatToDo = pickRandomlyBetween(Direction.NORTH, Direction.EAST);
                }else if (okayToGoNorth() || okayToGoEast()){
                    whatToDo = preferInOrder(Direction.EAST, Direction.NORTH);
                    //}else if(me.currentObjective == Objective.SEEK_ENEMY_BASE){
                    //whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(Direction.EAST, Direction.NORTH, Direction.SOUTH, Direction.WEST);
                }
                break;
            case NORTHWEST:
                if(okayToGoNorth() && okayToGoWest()){
                    whatToDo = pickRandomlyBetween(Direction.NORTH, Direction.WEST);
                    //whatToDo = preferInOrder(Direction.WEST, Direction.NORTH);
                }else if(okayToGoNorth() || okayToGoWest()){
                    whatToDo = preferInOrder(Direction.WEST, Direction.NORTH);
                    //}else if(me.currentObjective == Objective.SEEK_ENEMY_BASE){
                    //     whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(Direction.WEST, Direction.NORTH, Direction.SOUTH, Direction.EAST);
                }
                break;
            case SOUTH:
                if(okayToGoSouth()){
                    whatToDo = moveSouth();
                    //}else if(me.currentObjective == Objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(Direction.SOUTH, Direction.EAST, Direction.WEST, Direction.NORTH);
                }

                break;
            case SOUTHEAST:
                if(okayToGoSouth() && okayToGoEast()){
                    whatToDo = pickRandomlyBetween(Direction.SOUTH, Direction.EAST);
                    //whatToDo = preferInOrder(Direction.EAST, Direction.SOUTH);
                }else if(okayToGoSouth() || okayToGoEast()){
                    whatToDo = preferInOrder(Direction.EAST, Direction.SOUTH);
                    //}else if(me.currentObjective == Objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(Direction.EAST, Direction.SOUTH, Direction.NORTH, Direction.WEST);
                }
                break;
            case SOUTHWEST:
                if(okayToGoSouth() && okayToGoWest()){
                    whatToDo = pickRandomlyBetween(Direction.SOUTH, Direction.WEST);
                    //whatToDo = preferInOrder(Direction.WEST, Direction.SOUTH);
                }else if(okayToGoSouth() || okayToGoWest()){
                    whatToDo = preferInOrder(Direction.WEST, Direction.SOUTH);
                    //}else if(me.currentObjective == Objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(Direction.WEST, Direction.SOUTH, Direction.NORTH, Direction.EAST);
                }

                break;
            case EAST:
                if(okayToGoEast()){
                    whatToDo = moveEast();
                    //}else if(me.currentObjective == Objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(Direction.EAST, Direction.SOUTH, Direction.NORTH, Direction.WEST);
                }
                break;
            case WEST:
                if(okayToGoWest()){
                    whatToDo = moveWest();
                    //}else if(me.currentObjective == Objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(Direction.WEST, Direction.NORTH, Direction.SOUTH, Direction.EAST);
                }
                break;
        }
        return whatToDo;
    }

    //MAP FUNCTIONS//MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS

    /*public ArrayList<Direction> getLeastVisitedSurroundingSquares(){
        ArrayList<Direction> leastVisited = new ArrayList<Direction>();

        int lowest = 200;

        int numNorth = (okayToGoNorth())? (getNumTimesVisited(me.position.oneNorth())) : (200);

        int numEast = (okayToGoEast()) ? (getNumTimesVisited(me.position.oneEast())) : (200);

        int numSouth = (okayToGoSouth()) ? (getNumTimesVisited(me.position.oneSouth())) : (200);

        int numWest = (okayToGoWest()) ? (getNumTimesVisited(me.position.oneWest())) : (200);

        if(numNorth < lowest){
            lowest = numNorth;
        }
        if(numEast < lowest){
            lowest = numEast;
        }
        if(numSouth < lowest){
            lowest = numSouth;
        }
        if(numWest < lowest){
            lowest = numWest;
        }
        if(numNorth == lowest){
            leastVisited.add(Direction.NORTH);
        }
        if(numEast == lowest){
            leastVisited.add(Direction.EAST);
        }
        if(numSouth == lowest){
            leastVisited.add(Direction.SOUTH);
        }
        if(numWest == lowest){
            leastVisited.add(Direction.WEST);
        }
        return leastVisited;
    }

    /*public int getNumTimesVisited(Coordinate pos){
        return timesVisited[pos.x][pos.y];
    }*/

    public int checkForSurroundingEnemyTharpoonAgentsWithOurFlag(){
        int whatToDo = doNothing;
        if(env.enemyNorthImmediate && env.enemyHasOurFlag){
            whatToDo = moveNorth;
        }else if(env.enemyEastImmediate && env.enemyHasOurFlag){
            whatToDo = moveEast;
        }
        else if(env.enemySouthImmediate && env.enemyHasOurFlag){
            whatToDo = moveSouth;
        }else if(env.enemyWestImmediate && env.enemyHasOurFlag) {
            whatToDo = moveWest;
        }
        return whatToDo;
    }

    public int goRandomOpenDirection(){
        ArrayList<Direction> freeDirections = freeDirections();
        Direction dir = Direction.DONOTHING;

        int num = randomInt(1, freeDirections.size());
        for(int i = 0; i < freeDirections.size(); i++){
            if(num == i){
                dir = freeDirections.get(i);
                break;
            }
        }
        return move(dir);
    }

    public int pickRandomlyBetween(Direction firstDir, Direction secondDir){
        Direction dir = Direction.DONOTHING;

        int num = randomInt(1, 2);
        return (num == 1) ? (move(firstDir)) : (move(secondDir));
    }

    public int randomInt(int min, int max){
        rand = new Random();
        return rand.nextInt((max - min) + 1) + min;
    }

    public int pickRandomlyBetween(ArrayList<Direction> Directions){
        Direction dir = Direction.DONOTHING;

        int num = randomInt(1, Directions.size());
        for(int i = 0; i < Directions.size(); i++){
            if(num == i){
                dir = Directions.get(i);
                break;
            }
        }
        return move(dir);
    }

    /*public int moveToOneOfLeastVisitedSquares(){
        int whatToDo = pickRandomlyBetween(getLeastVisitedSurroundingSquares());
        return whatToDo;
    }*/

    public ArrayList<Direction> freeDirections(){
        ArrayList<Direction> freeDirections = new ArrayList<Direction>();
        if(okayToGoNorth()){
            freeDirections.add(Direction.NORTH);
        }
        if(okayToGoEast()) {
            freeDirections.add(Direction.EAST);
        }
        if(okayToGoSouth()) {
            freeDirections.add(Direction.SOUTH);
        }
        if(okayToGoWest()){
            freeDirections.add(Direction.WEST);
        }
        return freeDirections;
    }

    public boolean DirectionsOkay(Direction firstDirection, Direction secondDirection){
        return (okayToGo(firstDirection) && okayToGo(secondDirection));
    }

    public boolean oscillatingMoveCheck(){
        if(me.squaresTravelled.size() < 3){
            return false;
        }else{
            return (getXPositionsBack(2).isEqualTo(me.position));
        }
    }

    public boolean smallCircleCheck(){
        boolean hasCircle = false;

        if(me.squaresTravelled.size() < 5){
            return false;
        }

        /*int d = dir.ordinal();
        for(int i = 0; i < 4; i++){
            if(getDirectionFromTharpoonAgentAction(getXMovesBack(4)).ordinal() == d) {
                hasCircle = true;
            }
                d++;
        }*/
        Coordinate fourPositionsBack = getXPositionsBack(4);
        if(fourPositionsBack == me.position){
            //then I have gone in a small circle
            //System.out.println("mp: " + me.position.toString() + " 4pb: " + fourPositionsBack.toString());
            //System.out.println("CIRCLE!!!");
            hasCircle = true;
        }
        return hasCircle;
    }

    public Coordinate getLastPosition(){
        return me.squaresTravelled.get(me.squaresTravelled.size() - 2);
    }

    public Coordinate getXPositionsBack(Integer x){
        Coordinate xPosback = me.squaresTravelled.get(me.squaresTravelled.size() - (x + 1));
        return xPosback;
    }

    public int getLastMove(){
        return me.movesMade.get(me.movesMade.size() - 2);
    }

    public int getXMovesBack(Integer x){
        return me.movesMade.get(me.movesMade.size() - (x + 1));
    }

    public Direction getOppositeDirection(Direction dir){
        Direction opposite = Direction.DONOTHING;
        switch(dir){
            case NORTH:
                opposite = Direction.SOUTH;
                break;
            case NORTHEAST:
                opposite = Direction.SOUTHWEST;
                break;
            case EAST:
                opposite = Direction.WEST;
                break;
            case SOUTHEAST:
                opposite = Direction.NORTHWEST;
                break;
            case SOUTH:
                opposite = Direction.NORTH;
                break;
            case SOUTHWEST:
                opposite = Direction.NORTHEAST;
                break;
            case WEST:
                opposite = Direction.EAST;
                break;
            case NORTHWEST:
                opposite = Direction.SOUTHEAST;
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
        }else if (getLastMove() == moveEast && okayToGoWest()){
            return moveWest();
        }else if (getLastMove() == moveWest && okayToGoEast()){
            return moveEast();
        }else{
            return doNothing;
        }
    }

    /*public int plantMine(){
        changeMyPosition(me.position, me.position);  //I'm not moving, but call this function for bookkeeping.
        setMapSquare(me.position, 'm');
        me.movesMade.add(plantMine);
        possibleMines.add(me.position);
        return plantMine;
    }*/

    public int moveNorth(){
        Coordinate newPosition = new Coordinate(me.position.x, me.position.y - 1);
        map.changeMyPosition(env, me, me.position, newPosition);
        me.movesMade.add(moveNorth);
        return moveNorth;
    }

    public int moveEast(){
        Coordinate newPosition = new Coordinate(me.position.x + 1, me.position.y);
        map.changeMyPosition(env, me, me.position, newPosition);
        me.movesMade.add(moveEast);
        return moveEast;
    }

    public int moveSouth(){
        Coordinate newPosition = new Coordinate(me.position.x, me.position.y + 1);
        map.changeMyPosition(env, me, me.position, newPosition);
        me.movesMade.add(moveSouth);
        return moveSouth;
    }

    public int moveWest(){
        Coordinate newPosition = new Coordinate(me.position.x - 1, me.position.y);
        map.changeMyPosition(env, me, me.position, newPosition);
        me.movesMade.add(moveWest);
        return moveWest;
    }

    public int preferInOrder(Direction firstDirection, Direction secondDirection) {
        int whatToDo = doNothing;
        if (okayToGo(firstDirection)) {
            whatToDo = move(firstDirection);
        } else if (okayToGo(secondDirection)) {
            whatToDo = move(secondDirection);
        }
        return whatToDo;
    }

    public int preferInOrder(Direction firstDirection, Direction secondDirection, Direction thirdDirection, Direction fourthDirection){
        int whatToDo = doNothing;
        if(okayToGo(firstDirection)){
            whatToDo = move(firstDirection);
        }else if(okayToGo(secondDirection)){
            whatToDo = move(secondDirection);
        }else if(okayToGo(thirdDirection)){
            whatToDo = move(thirdDirection);
        }else if(okayToGo(fourthDirection)){
            whatToDo = move(fourthDirection);
        }else{
            whatToDo = doNothing;
        }
        return whatToDo;
    }

    boolean okayToGo(Direction dir){
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

    int move(Direction dir){
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



    public void determineDefenseWallCenterPositionAndDirection(){

        if(env.enemyBaseWest){
            defenseWallCenter.position.x = ourBase.position.x - 2;
        }else{
            defenseWallCenter.position.x = ourBase.position.x + 2;
        }
        defenseWallCenter.position.y = ourBase.position.y;
        System.out.println("determined defense wall center " + defenseWallCenter.position.toString());

        if(positionIsNorthEast(defenseWallCenter.position)){
            defenseWallCenter.dir = Direction.NORTHEAST;
        }else if(positionIsNorthWest(defenseWallCenter.position)){
            defenseWallCenter.dir = Direction.NORTHWEST;
        }else if(positionIsSouthEast(defenseWallCenter.position)){
            defenseWallCenter.dir = Direction.SOUTHEAST;
        }else if(positionIsSouthWest(defenseWallCenter.position)){
            defenseWallCenter.dir = Direction.SOUTHWEST;
        }else if(positionIsNorth(defenseWallCenter.position)){
            defenseWallCenter.dir = Direction.NORTH;
        }else if(positionIsEast(defenseWallCenter.position)){
            defenseWallCenter.dir = Direction.EAST;
        }else if(positionIsSouth(defenseWallCenter.position)){
            defenseWallCenter.dir = Direction.SOUTH;
        }else{
            defenseWallCenter.dir = Direction.WEST;
        }
    }

    /*public void updateTimesVisited(Coordinate pos){
        timesVisited[pos.x][pos.y]++;
    }*/

    /*public void makeEmptyTimesVisited(){
        timesVisited = new int[mapHeight][mapHeight];
        for(int i = 0; i < mapHeight; i++){
            for(int j = 0; j < mapHeight; j++){
                timesVisited[i][j] = 0;
            }
        }
    }*/

   /* public void printMap() {

        map[ourBase.position.x][ourBase.position.y] = 'O';
        map[enemyBase.position.x][enemyBase.position.y] = 'E';

        for (int i = 0; i < TharpoonAgents.size(); i++) {
            map[TharpoonAgents.get(i).position.x][TharpoonAgents.get(i).position.y] = TharpoonAgents.get(i).name;
        }

        System.out.println("----------");
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapHeight; j++) {
                System.out.print(map[j][i]);
            }
            System.out.println();
        }
        System.out.println("----------");
    }*/

    //TharpoonEnvironment FUNCTIONS//TharpoonEnvironment FUNCTIONS //TharpoonEnvironment FUNCTIONS //TharpoonEnvironment FUNCTIONS //TharpoonEnvironment FUNCTIONS //TharpoonEnvironment FUNCTIONS

    public boolean okayToGoNorth() {
        //Coordinate oneNorth = new Coordinate(me.position.x, me.position.y - 1);
        //boolean hasPossibleMine = possibleMines.contains(oneNorth);
        return ((me.hasFlag && env.enemyNorthImmediate) || env.friendlyNorthImmediate || env.obstNorth || (env.ourBaseNorthImmediate && !me.hasFlag)) ? (false) : (true);
    }

    public boolean okayToGoEast() {
        //Coordinate oneEast = new Coordinate(me.position.x + 1, me.position.y);
        //boolean hasPossibleMine = possibleMines.contains(oneEast);
        return ((me.hasFlag && env.enemyEastImmediate) || env.friendlyEastImmediate || env.obstEast || (env.ourBaseEastImmediate && !me.hasFlag)) ? (false) : (true);
    }

    public boolean okayToGoWest() {
        //Coordinate oneWest = new Coordinate(me.position.x - 1, me.position.y);
        //boolean hasPossibleMine = possibleMines.contains(oneWest);
        return ((me.hasFlag && env.enemyWestImmediate)|| env.friendlyWestImmediate || env.obstWest || (env.ourBaseWestImmediate && !me.hasFlag)) ? (false) : (true);
    }

    public boolean okayToGoSouth() {
        //Coordinate oneSouth = new Coordinate(me.position.x, me.position.y + 1);
        //boolean hasPossibleMine = possibleMines.contains(oneSouth);
        return ((me.hasFlag && env.enemySouthImmediate) || env.friendlySouthImmediate || env.obstSouth || (env.ourBaseSouthImmediate && !me.hasFlag)) ? (false) : (true);
    }

    public void queryEnvironment(AgentEnvironment inEnvironment) {

        env.environmentHandle = inEnvironment;

        //do I currently have the flag
        me.hasFlag = inEnvironment.hasFlag();
        env.enemyHasOurFlag = inEnvironment.hasFlag(inEnvironment.ENEMY_TEAM);

        //Direction of our base
        env.ourBaseWest = inEnvironment.isBaseWest(inEnvironment.OUR_TEAM, false);
        env.ourBaseEast = inEnvironment.isBaseEast(inEnvironment.OUR_TEAM, false);
        env.ourBaseSouth = inEnvironment.isBaseSouth(inEnvironment.OUR_TEAM, false);
        env.ourBaseNorth = inEnvironment.isBaseNorth(inEnvironment.OUR_TEAM, false);

        //immediate presence of our base
        env.ourBaseWestImmediate = inEnvironment.isBaseWest(inEnvironment.OUR_TEAM, true);
        env.ourBaseEastImmediate = inEnvironment.isBaseEast(inEnvironment.OUR_TEAM, true);
        env.ourBaseSouthImmediate = inEnvironment.isBaseSouth(inEnvironment.OUR_TEAM, true);
        env.ourBaseNorthImmediate = inEnvironment.isBaseNorth(inEnvironment.OUR_TEAM, true);

        //Direction of enemy base
        env.enemyBaseEast = inEnvironment.isBaseEast(inEnvironment.ENEMY_TEAM, false);
        env.enemyBaseWest = inEnvironment.isBaseWest(inEnvironment.ENEMY_TEAM, false);
        env.enemyBaseNorth = inEnvironment.isBaseNorth(inEnvironment.ENEMY_TEAM, false);
        env.enemyBaseSouth = inEnvironment.isBaseSouth(inEnvironment.ENEMY_TEAM, false);

        //immediate presence of enemy base
        env.enemyBaseEastImmediate = inEnvironment.isBaseEast(inEnvironment.ENEMY_TEAM, true);
        env.enemyBaseWestImmediate = inEnvironment.isBaseWest(inEnvironment.ENEMY_TEAM, true);
        env.enemyBaseNorthImmediate = inEnvironment.isBaseNorth(inEnvironment.ENEMY_TEAM, true);
        env.enemyBaseSouthImmediate = inEnvironment.isBaseSouth(inEnvironment.ENEMY_TEAM, true);

        //presence of surrounding obstacles
        env.obstNorth = inEnvironment.isObstacleNorthImmediate();
        env.obstSouth = inEnvironment.isObstacleSouthImmediate();
        env.obstEast  = inEnvironment.isObstacleEastImmediate();
        env.obstWest  = inEnvironment.isObstacleWestImmediate();

        env.obstNorthEast = (env.obstNorth && env.obstEast);
        env.obstSouthEast = (env.obstSouth && env.obstEast);
        env.obstNorthWest = (env.obstNorth && env.obstWest);
        env.obstSouthWest = (env.obstSouth && env.obstWest);

        env.obstNorthEastSouth = (env.obstNorth && env.obstEast && env.obstSouth);
        env.obstEastSouthWest = (env.obstEast && env.obstSouth && env.obstWest);
        env.obstSouthWestNorth = (env.obstSouth && env.obstWest && env.obstNorth);
        env.obstWestNorthEast = (env.obstWest && env.obstNorth && env.obstEast);
        env.obstEveryDirection = (env.obstWest && env.obstNorth && env.obstEast && env.obstSouth);

        //immediate presence of enemy
        env.enemyNorthImmediate = inEnvironment.isAgentNorth(inEnvironment.ENEMY_TEAM, true);
        env.enemyEastImmediate = inEnvironment.isAgentEast(inEnvironment.ENEMY_TEAM, true);
        env.enemySouthImmediate = inEnvironment.isAgentSouth(inEnvironment.ENEMY_TEAM, true);
        env.enemyWestImmediate = inEnvironment.isAgentWest(inEnvironment.ENEMY_TEAM, true);

        //immediate presence of friendly Agent
        env.friendlyNorthImmediate = inEnvironment.isAgentNorth(inEnvironment.OUR_TEAM, true);
        env.friendlyEastImmediate = inEnvironment.isAgentEast(inEnvironment.OUR_TEAM, true);
        env.friendlySouthImmediate = inEnvironment.isAgentSouth(inEnvironment.OUR_TEAM, true);
        env.friendlyWestImmediate = inEnvironment.isAgentWest(inEnvironment.OUR_TEAM, true);

        //update the Direction for all points of interest
        for (int i = 0; i < pointsOfInterest.size(); i++) {
            if (pointsOfInterest.get(i).name == "ourBase") {
                if (env.ourBaseNorth && env.ourBaseEast) {
                    pointsOfInterest.get(i).dir = Direction.NORTHEAST;
                } else if (env.ourBaseEast && env.ourBaseSouth) {
                    pointsOfInterest.get(i).dir = Direction.SOUTHEAST;
                } else if (env.ourBaseWest && env.ourBaseSouth) {
                    pointsOfInterest.get(i).dir = Direction.SOUTHWEST;
                } else if (env.ourBaseWest && env.ourBaseNorth) {
                    pointsOfInterest.get(i).dir = Direction.NORTHWEST;
                } else if (env.ourBaseNorth) {
                    pointsOfInterest.get(i).dir = Direction.NORTH;
                } else if (env.ourBaseEast) {
                    pointsOfInterest.get(i).dir = Direction.EAST;
                } else if (env.ourBaseWest) {
                    pointsOfInterest.get(i).dir = Direction.WEST;
                } else if (env.ourBaseSouth) {
                    pointsOfInterest.get(i).dir = Direction.SOUTH;
                }
            } else if (pointsOfInterest.get(i).name == "enemyBase") {
                if (env.enemyBaseNorth && env.enemyBaseEast) {
                    pointsOfInterest.get(i).dir = Direction.NORTHEAST;
                } else if (env.enemyBaseEast && env.enemyBaseSouth) {
                    pointsOfInterest.get(i).dir = Direction.SOUTHEAST;
                } else if (env.enemyBaseWest && env.enemyBaseSouth) {
                    pointsOfInterest.get(i).dir = Direction.SOUTHWEST;
                } else if (env.enemyBaseWest && env.enemyBaseNorth) {
                    pointsOfInterest.get(i).dir = Direction.NORTHWEST;
                } else if (env.enemyBaseNorth) {
                    pointsOfInterest.get(i).dir = Direction.NORTH;
                } else if (env.enemyBaseEast) {
                    pointsOfInterest.get(i).dir = Direction.EAST;
                } else if (env.enemyBaseWest) {
                    pointsOfInterest.get(i).dir = Direction.WEST;
                } else if (env.enemyBaseSouth) {
                    pointsOfInterest.get(i).dir = Direction.SOUTH;
                }
            }
        }
    }

    public boolean positionIsNorth(Coordinate pos){
        return (me.position.y > pos.y);
    }

    public boolean positionIsSouth(Coordinate pos){
        return (me.position.y < pos.y);
    }

    public boolean positionIsEast(Coordinate pos){
        return (me.position.x < pos.x);
    }

    public boolean positionIsWest(Coordinate pos){
        return (me.position.x > pos.x);
    }

    public boolean positionIsNorthEast(Coordinate pos){
        return (positionIsNorth(pos) && positionIsEast(pos));
    }

    public boolean positionIsSouthEast(Coordinate pos){
        return (positionIsSouth(pos) && positionIsEast(pos));
    }

    public boolean positionIsNorthWest(Coordinate pos){
        return (positionIsNorth(pos) && positionIsWest(pos));
    }

    public boolean positionIsSouthWest(Coordinate pos){
        return (positionIsSouth(pos) && positionIsWest(pos));
    }

    public Direction getOnlyFreeDirection() {
        Direction freeDirection = Direction.EAST;
        if (env.obstNorthEastSouth) {
            freeDirection = Direction.WEST;
        } else if (env.obstEastSouthWest) {
            freeDirection = Direction.NORTH;
        } else if (env.obstSouthWestNorth) {
            freeDirection = Direction.EAST;
        } else if (env.obstWestNorthEast) {
            freeDirection = Direction.SOUTH;
        }
        return freeDirection;
    }

    //STRING CONVERSION FUNCTIONS //STRING CONVERSION FUNCTIONS //STRING CONVERSION FUNCTIONS //STRING CONVERSION FUNCTIONS
    public String getNameFromTharpoonAgentAction(int action) {
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

    public String getDirectionName(Direction dir) {
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

    public int getTharpoonAgentActionFromDirection(Direction dir) {
        int action = doNothing;

        switch (dir) {
            case NORTH:
                action = moveNorth;
                break;
            case EAST:
            case NORTHEAST:
            case SOUTHEAST:
                action = moveEast;
                break;
            case WEST:
            case NORTHWEST:
            case SOUTHWEST:
                action = moveWest;
                break;
            case SOUTH:
                action = moveSouth;
                break;
        }
        return action;
    }

    public Direction getDirectionFromTharpoonAgentAction(int lastAction){
        Direction dir = Direction.DONOTHING;
        if(lastAction == moveNorth){
            dir = Direction.NORTH;
        }else if(lastAction == moveEast){
            dir = Direction.EAST;
        }else if(lastAction == moveWest){
            dir = Direction.WEST;
        }else{
            dir = Direction.SOUTH;
        }
        return dir;
    }
}