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

public class Tharpoon5 extends Agent {

    private class Agent {
        public Integer number;
        public char name;
        public ArrayList<objective> objectives;
        public Coordinate spawn;
        public Coordinate position;
        public ArrayList<Coordinate> squaresTravelled;
        public ArrayList<Integer> movesMade;
        public boolean hasFlag;

        public Agent() {
            number = -1;
            objectives = new ArrayList<objective>();
            pushObjective(objective.INITIALIZE);
            spawn = new Coordinate();
            position = new Coordinate();
            squaresTravelled = new ArrayList<Coordinate>();
            movesMade = new ArrayList<Integer>();
            hasFlag = false;
        }

        public objective getCurrentObjective() {
            return objectives.get(objectives.size() - 1);
        }

        public String getCurrentObjectiveString(){

            String objectiveString = "";

            switch(getCurrentObjective()){
                case INITIALIZE:
                    objectiveString = "initialize";
                    break;
                case SEEK_ENEMY_BASE:
                    objectiveString = "SEEK ENEMY BASE";
                    break;
                case SEEK_OUR_BASE:
                    objectiveString = "SEEK OUR BASE";
                    break;
                case RETRIEVE_FRIENDLY_FLAG:
                    objectiveString = "SEEK FRIENDLY FLAG";
                    break;
                case DEFEND_OUR_BASE:
                    objectiveString = "DEFEND OUR BASE";
                    break;
                case MOVE_AROUND_OBSTACLE:
                    objectiveString = "MOVE AROUND OBSTACLE";
                    break;
            }
            return objectiveString;
        }

        public objective getXObjectivesBack(int x) {
            return objectives.get((objectives.size() - 1) - x);
        }

        public Agent setNewCurrentObjective(objective newObjective) {
            popObjective();
            pushObjective(newObjective);
            return this;
        }

        public Agent setNewBaseObjective(objective newObjective){
            objectives.set(0, newObjective);
            return this;
        }

        public objective getBaseObjective(){
            return objectives.get(0);
        }

        public Agent pushObjective(objective newObjective) {
            objectives.add(newObjective);
            return this;
        }

        public Agent popObjective() {
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
        direction dir;
        Coordinate position;

        Place(String name) {
            this.name = name;
            position = new Coordinate();
        }
    }

    private class Coordinate{
        public Integer x;
        public Integer y;

        public Coordinate() {
        }

        public Coordinate(Integer x, Integer y) {
            this.x = x;
            this.y = y;
        }

        public Coordinate(Coordinate otherCoordinate){
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

        public boolean isEqualTo(Coordinate otherCoordinate){
            return ((this.x == otherCoordinate.x) && (this.y == otherCoordinate.y));
        }

        public Coordinate oneNorth(){
            return new Coordinate(this.x, this.y - 1);
        }

        public Coordinate oneSouth(){
            return new Coordinate(x, y + 1);
        }

        public Coordinate oneEast(){
            return new Coordinate(x + 1, y);
        }

        public Coordinate oneWest(){
            return new Coordinate(x - 1, y);
        }
    }

    //Agents
    private final static int MAX_NUM_AGENTS = 2;
    private static ArrayList<Agent> agents = new ArrayList<Agent>();
    private Agent me;
    private Agent otherAgent;

    private enum objective {INITIALIZE, SEEK_ENEMY_BASE, SEEK_OUR_BASE, RETRIEVE_FRIENDLY_FLAG, DEFEND_OUR_BASE, MOVE_AROUND_OBSTACLE}


    //Map
    private static char[][] map;
    private int[][] timesVisited;
    private int mapHeight = 10;         //it is known that mapHeight == mapLength
    Place ourBase;
    Place enemyBase;
    Place defenseWallCenter;
    ArrayList<Place> pointsOfInterest = new ArrayList<Place>();
    ArrayList<Coordinate> possibleMines = new ArrayList<Coordinate>();

    private enum direction {NORTH, EAST, SOUTH, WEST, SOUTHWEST, SOUTHEAST, NORTHEAST, NORTHWEST, DONOTHING}

    //Strategy
    boolean oneDefenderOneOffender = false;


    //Environment Variables
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

    private int moveNorth = AgentAction.MOVE_NORTH;
    private int moveEast = AgentAction.MOVE_EAST;
    private int moveSouth = AgentAction.MOVE_SOUTH;
    private int moveWest = AgentAction.MOVE_WEST;
    private int doNothing = AgentAction.DO_NOTHING;
    private int plantMine = AgentAction.PLANT_HYPERDEADLY_PROXIMITY_MINE;

    Random rand;


    public Tharpoon5() {

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
        makeEmptyTimesVisited();
        ourBase = new Place("ourBase");
        enemyBase = new Place("enemyBase");
        defenseWallCenter = new Place("defenseWallCenter");
        pointsOfInterest.add(ourBase);
        pointsOfInterest.add(enemyBase);
        pointsOfInterest.add(defenseWallCenter);
    }

    public int getMove(AgentEnvironment inEnvironment) {

        int whatToDo = doNothing;

        //init
        queryEnvironment(inEnvironment);

        //some initilizations before we start seeking
        if (me.getCurrentObjective() == objective.INITIALIZE) {
            determineMySpawnAndInitialPosition();
            if (me.number == agents.size() - 1) {
                determineBasePositions();
            }
        }

        amIAtSpawn();
        addSurroundingObstaclesToMap(inEnvironment);
        if (me.hasFlag) {
            me.setNewBaseObjective(objective.SEEK_OUR_BASE);
        }else{
            me.setNewBaseObjective(objective.SEEK_ENEMY_BASE);
        }

        switch (me.getCurrentObjective()) {
            case SEEK_ENEMY_BASE:
                whatToDo = seek(enemyBase);
                break;
            case SEEK_OUR_BASE:
                whatToDo = seek(ourBase);
                break;
            case DEFEND_OUR_BASE:
                whatToDo = defend(ourBase);
                break;
            case MOVE_AROUND_OBSTACLE:
                if(me.getBaseObjective() == objective.SEEK_OUR_BASE){
                    whatToDo = goAroundObstacle(ourBase);
                }else if(me.getBaseObjective() == objective.SEEK_ENEMY_BASE){
                    whatToDo = goAroundObstacle(enemyBase);
                }
        }

        //print only after every complete move (ie, both agents have moved)
        if (me.number == 1) {
            printMap();
        }

        return whatToDo;

    }

    public int seek2(Place pointOfInterest){
        int whatToDo = AgentAction.DO_NOTHING;

        switch(pointOfInterest.dir){
            case NORTH:
                if(okayToGoNorth()){
                    whatToDo = moveNorth();
                }
                break;
            case NORTHEAST:
                // pick north or east for move with 50/50 chance
                if( Math.random() < 0.5 && okayToGoNorth() ) {
                    whatToDo = moveNorth();
                }
                else if( okayToGoEast() ) {
                    whatToDo = moveEast();
                }
                else if( okayToGoNorth() ) {
                    whatToDo = moveNorth();
                }break;
            case NORTHWEST:
                // pick north or west for move with 50/50 chance
                if( Math.random() < 0.5 && okayToGoNorth() ) {
                    whatToDo = moveNorth();
                }
                else if( okayToGoWest() ) {
                    whatToDo = moveWest();
                }
                else if( okayToGoNorth() ) {
                    whatToDo = moveNorth();
                }
                break;
            case SOUTH:
                if( okayToGoSouth() ) {
                    // move south
                    whatToDo = moveSouth();
                }
                break;
            case SOUTHEAST:
                if( Math.random() < 0.5 && okayToGoSouth() ) {
                    whatToDo = moveSouth();
                }
                else if( okayToGoEast() ) {
                    whatToDo = moveEast();
                }
                else if( okayToGoSouth() ) {
                    whatToDo = moveEast();
                }
                break;
            case SOUTHWEST:
                if( Math.random() < 0.5 && okayToGoSouth()) {
                    whatToDo = moveSouth();
                }
                else if( okayToGoWest() ) {
                    whatToDo = moveWest();
                }
                else if( okayToGoSouth() ) {
                    whatToDo = moveSouth();
                }
                break;
            case EAST:
                if( okayToGoEast() ) {
                    whatToDo = moveEast();
                }
                break;
            case WEST:
                if( okayToGoWest() ) {
                    whatToDo = moveWest();
                }break;
            default:
                if( okayToGoNorth() ) {
                    whatToDo = moveNorth();
                }
                else if( okayToGoSouth() ) {
                    whatToDo = moveSouth();
                }
                else if( okayToGoEast() ) {
                    whatToDo = moveEast();
                }
                else if( okayToGoWest() ) {
                    whatToDo = moveWest();
                }
                else {
                    // completely obst!
                    whatToDo = AgentAction.DO_NOTHING;
                }
        }
        System.out.println("agent " + me.name + me.number + " " + getNameFromAgentAction(whatToDo) + " to " + me.position.toString());
        return whatToDo;
    }

    public int defend(Place place){
        determineDefenseWallCenterPositionAndDirection();

        int whatToDo = doNothing;

        if(inDefendingWallArea()){
            System.out.println("create wall");
            whatToDo = createDefendingWall();
        }else{
            System.out.println("seek wall center which is " + getDirectionName(defenseWallCenter.dir));
            whatToDo = seek(defenseWallCenter);
        }

        return whatToDo;
    }

    public boolean inDefendingWallArea(){
        return (me.position.isEqualTo(defenseWallCenter.position) ||
                me.position.isEqualTo(defenseWallCenter.position.oneNorth()) ||
                me.position.isEqualTo(defenseWallCenter.position.oneSouth()));
    }

    public int createDefendingWall(){

        boolean mineNorth = possibleMines.contains(me.position.oneNorth());
        boolean mineSouth = possibleMines.contains(me.position.oneSouth());
        boolean mineEast = possibleMines.contains(me.position.oneEast());
        boolean mineWest = possibleMines.contains(me.position.oneWest());
        boolean onMine = possibleMines.contains(me.position);

        boolean oneNorth = me.position.isEqualTo(defenseWallCenter.position.oneNorth());
        boolean oneSouth = me.position.isEqualTo(defenseWallCenter.position.oneSouth());
        boolean onCenter = me.position.isEqualTo(defenseWallCenter.position);

        int whatToDo = doNothing;

        //if I am on the wall center and there's not a mine or an obstacle south, move south
        if(onCenter && !mineSouth && !obstSouth) {
            whatToDo = moveSouth();

            //If I am one south of the center and I am not standing on a mine, plant one
        }else if(oneSouth && !onMine) {
            whatToDo = plantMine();

            //if I am one south of the center and I am standing on a mine, move north
        }else if(oneSouth && onMine){
            whatToDo = moveNorth();

            //if there is not a mine on defense wall center, put one there
        }else if (onCenter && !onMine){
            whatToDo = plantMine();

            //if I am on the defense wall center and I am standing on a mine, move north
        }else if(me.position.isEqualTo(defenseWallCenter.position) && onMine){
            whatToDo = moveNorth();

            //if I am one north of the defense wall center and I am not standing on a mine, plant one
        }else if(oneNorth && !onMine){
            whatToDo = plantMine();

            //if I am one north of the defense wall center and I am standing on a mine, seek enemy base because I have built the little wall
        }else if(oneNorth && onMine){
            me.setNewCurrentObjective(objective.SEEK_ENEMY_BASE);
            whatToDo = seek(enemyBase);
        }
        return whatToDo;
    }

    public int seek(Place place) {

        int whatToDo = doNothing;
        System.out.println("agent " + me.name + " has obj " + me.getCurrentObjectiveString());

        if (obstInThreeDirections()) {
            whatToDo = getAgentActionFromDirection(getOnlyNonObstDirection());
            return whatToDo;
        }
        if(blockedInThreeDirections()){
            whatToDo = getAgentActionFromDirection(getOnlyFreeDirection());
            return whatToDo;
        }

        direction directionToGo = place.dir;

        //if(oscillatingMoveCheck()){
        //    directionToGo = getDirectionFromAgentAction(getXMovesBack(2));
        //}

        //int tagEnemyWithOurFlag = checkForSurroundingEnemyAgentsWithOurFlag();
        //if(tagEnemyWithOurFlag != doNothing){
        //    return tagEnemyWithOurFlag;
        //}

        //if(smallCircleCheck()){
        //    return goRandomOpenDirection();
        //}

        switch (directionToGo) {
            case NORTH:
                if (okayToGoNorth()) {
                    whatToDo = moveNorth();
                    //}else if(me.currentObjective == objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    if(obstNorth){
                        me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                        whatToDo = goAroundObstacle(place);
                    }
                    else{
                        whatToDo = moveRandomlyOneOfTheseDirectionsIfOpenOrElseDoNothing(direction.EAST, direction.WEST);
                    }//whatToDo = goRandomOpenDirection();
                    //whatToDo = preferInOrder(direction.NORTH, direction.EAST, direction.WEST, direction.SOUTH);
                }
                break;
            case NORTHEAST:
                if(okayToGoNorth() && okayToGoEast()){
                    //whatToDo = preferInOrder(direction.EAST, direction.NORTH);
                    whatToDo = pickRandomlyBetweenAndMove(direction.NORTH, direction.EAST);
                }else if (okayToGoNorth() || okayToGoEast()){
                    direction dir = pickRandomlyBetween(direction.EAST, direction.NORTH);
                    if(okayToGo(dir)){
                        whatToDo = move(dir);
                    }else {
                        if (dir == direction.EAST) {
                            whatToDo = moveNorth();
                        } else {
                            whatToDo = moveEast();
                        }
                    }
                    //whatToDo = preferInOrder(direction.EAST, direction.NORTH);
                    //}else if(me.currentObjective == objective.SEEK_ENEMY_BASE){
                    //whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(direction.EAST, direction.NORTH, direction.SOUTH, direction.WEST);
                }
                break;
            case NORTHWEST:
                if(okayToGoNorth() && okayToGoWest()){
                    whatToDo = pickRandomlyBetweenAndMove(direction.NORTH, direction.WEST);
                    //whatToDo = preferInOrder(direction.WEST, direction.NORTH);
                }else if(okayToGoNorth() || okayToGoWest()){
                    direction dir = pickRandomlyBetween(direction.WEST, direction.NORTH);
                    if(okayToGo(dir)){
                        whatToDo = move(dir);
                    }else{
                        if(dir == direction.WEST){
                            whatToDo = moveNorth();
                        }else{
                            whatToDo = moveWest();
                        }
                    }
                    //whatToDo = preferInOrder(direction.WEST, direction.NORTH);
                    //}else if(me.currentObjective == objective.SEEK_ENEMY_BASE){
                    //     whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(direction.WEST, direction.NORTH, direction.SOUTH, direction.EAST);
                }
                break;
            case SOUTH:
                if(okayToGoSouth()){
                    whatToDo = moveSouth();
                    //}else if(me.currentObjective == objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    if(obstSouth){
                        me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                        whatToDo = goAroundObstacle(place);
                    }else{
                        whatToDo = moveRandomlyOneOfTheseDirectionsIfOpenOrElseDoNothing(direction.EAST, direction.WEST);
                    }
                    //whatToDo = goRandomOpenDirection();
                    //whatToDo = preferInOrder(direction.SOUTH, direction.EAST, direction.WEST, direction.NORTH);
                }

                break;
            case SOUTHEAST:
                if(okayToGoSouth() && okayToGoEast()){
                    whatToDo = pickRandomlyBetweenAndMove(direction.SOUTH, direction.EAST);
                    //whatToDo = preferInOrder(direction.EAST, direction.SOUTH);
                }else if(okayToGoSouth() || okayToGoEast()){
                    direction dir = pickRandomlyBetween(direction.SOUTH, direction.EAST);
                    if(okayToGo(dir)){
                        whatToDo = move(dir);
                    }else{
                        if(dir == direction.SOUTH){
                            whatToDo = moveEast();
                        }else{
                            whatToDo = moveSouth();
                        }
                    }
                    //whatToDo = preferInOrder(direction.EAST, direction.SOUTH);
                    //}else if(me.currentObjective == objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(direction.EAST, direction.SOUTH, direction.NORTH, direction.WEST);
                }
                break;
            case SOUTHWEST:
                if(okayToGoSouth() && okayToGoWest()){
                    whatToDo = pickRandomlyBetweenAndMove(direction.SOUTH, direction.WEST);
                    //whatToDo = preferInOrder(direction.WEST, direction.SOUTH);
                }else if(okayToGoSouth() || okayToGoWest()){
                    direction dir = pickRandomlyBetween(direction.SOUTH, direction.WEST);
                    if(okayToGo(dir)){
                        whatToDo = move(dir);
                    }else{
                        if(dir == direction.SOUTH){
                            whatToDo = moveWest();
                        }else{
                            whatToDo = moveSouth();
                        }
                    }
                    //whatToDo = preferInOrder(direction.WEST, direction.SOUTH);
                    //}else if(me.currentObjective == objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    //whatToDo = goRandomOpenDirection();
                    whatToDo = preferInOrder(direction.WEST, direction.SOUTH, direction.NORTH, direction.EAST);
                }

                break;
            case EAST:
                if(okayToGoEast()){
                    whatToDo = moveEast();
                    //}else if(me.currentObjective == objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    if(obstEast){
                        whatToDo = goAroundObstacle(place);
                    }else{
                        whatToDo = moveRandomlyOneOfTheseDirectionsIfOpenOrElseDoNothing(direction.NORTH, direction.SOUTH);
                    }
                    //whatToDo = preferInOrder(direction.EAST, direction.SOUTH, direction.NORTH, direction.WEST);
                }
                break;
            case WEST:
                if(okayToGoWest()){
                    whatToDo = moveWest();
                    //}else if(me.currentObjective == objective.SEEK_ENEMY_BASE){
                    //    whatToDo = moveToOneOfLeastVisitedSquares();
                }else{
                    if(obstWest){
                        whatToDo = goAroundObstacle(place);
                    }else{
                        whatToDo = moveRandomlyOneOfTheseDirectionsIfOpenOrElseDoNothing(direction.NORTH, direction.SOUTH);
                    }
                    //whatToDo = goRandomOpenDirection();
                    //whatToDo = preferInOrder(direction.WEST, direction.NORTH, direction.SOUTH, direction.EAST);
                }
                break;
        }
        return whatToDo;
    }

    public int goAroundObstacle(Place pointOfInterest){

        int whatToDo = doNothing;

        System.out.println("hit obst on the way to " + pointOfInterest.name);

        //WALLS

        //EAST WALL
        //if obstEast and objective is south or southeast, keep going south until obstSouth or !obstEast

        //if obstEast and objective is north or northeast, keep going north until obstNorth or !obstEast

        //if obstEast and objective is east,
            //if last move was moveNorth keep going north until !obstEast or obstNorth

            //if last move was moveSouth keep going south until !obstEast or obstSouth

        //if obstEast and objective is west, go west

        //WEST WALL
        //if obstWest and objective is south or southwest, keep going south until obstSouth or !obstWest

        //if obstWest and objective is north or northwest, keep going north until obstNorth or !obstWest

        //if obstWest and objective is west,
            //if last move was moveNorth keep going north until !obstWest or obstNorth

            //if last move was moveSouth keep going south until !obstWest or obstSouth

        //if obstWest and objective is east, go east

        //NORTH WALL
        //if obstNorth and objective is east or northeast, keep going east until obstEast or !obstNorth

        //if obstNorth and objective is west or northwest, keep going west until obstWest or !obstNorth

        //if obstNorth and objective is north,
            //if last move was moveEast keep going east until !obstNorth or obstEast

            //if last move was moveWest keep going west until !obstNorth or obstWest

        //if obstNorth and objective is south, go south

        //SOUTH WALL
        //if obstSouth and objective is east or southeast, keep going east until obstEast or !obstSouth

        //if obstSouth and objective is west or southwest, keep going west until obstWest or !obstSouth

        //if obstSouth and objective is south,
        //if last move was moveEast keep going east until !obstSouth or obstEast

        //if last move was moveWest keep going west until !obstSouth or obstWest

        //if obstSouth and objective is north, go north

        //CORNERS
        //if obstEast and obstSouth, we are in a corner,
            //if our last move was moveSouth, keep going west until !obstSouth or obstWest

            //if our last move was moveEast, keep going north until !obstEast or obstNorth

        //if obstSouth and obstWest, we are in a corner, keep going north until !obstWest or obstNorth
            //if our last move was moveWest, keep going north until !obstWest or obstNorth

            //if our last move was moveSouth, keep going east until !obstSouth or obstEast

        //if obstWest and obstNorth, we are in a corner, keep going east until !obstNorth or obstEast
            //if our last move was moveWest, keep going south until !obstWest or obstSouth

            //if our last move was moveNorth, keep going east until !obstNorth or obstEast

        return whatToDo;
    }

    //MAP FUNCTIONS//MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS //MAP FUNCTIONS

    public ArrayList<direction> getLeastVisitedSurroundingSquares(){
        ArrayList<direction> leastVisited = new ArrayList<direction>();

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
            leastVisited.add(direction.NORTH);
        }
        if(numEast == lowest){
            leastVisited.add(direction.EAST);
        }
        if(numSouth == lowest){
            leastVisited.add(direction.SOUTH);
        }
        if(numWest == lowest){
            leastVisited.add(direction.WEST);
        }
        return leastVisited;
    }

    public int getNumTimesVisited(Coordinate pos){
        return timesVisited[pos.x][pos.y];
    }

    public int checkForSurroundingEnemyAgentsWithOurFlag(){
        int whatToDo = doNothing;
        if(enemyNorthImmediate && enemyHasOurFlag){
            whatToDo = moveNorth;
        }else if(enemyEastImmediate && enemyHasOurFlag){
            whatToDo = moveEast;
        }
        else if(enemySouthImmediate && enemyHasOurFlag){
            whatToDo = moveSouth;
        }else if(enemyWestImmediate && enemyHasOurFlag) {
            whatToDo = moveWest;
        }
        return whatToDo;
    }

    public int goRandomOpenDirection(){
        ArrayList<direction> freeDirections = freeDirections();
        direction dir = direction.DONOTHING;

        int num = randomInt(1, freeDirections.size());
        for(int i = 0; i < freeDirections.size(); i++){
            if(num == i){
                dir = freeDirections.get(i);
                break;
            }
        }
        return move(dir);
    }

    public int moveRandomlyOneOfTheseDirectionsIfOpenOrElseDoNothing(direction firstDir, direction secondDir){
        direction dir = pickRandomlyBetween(firstDir, secondDir);

        if(okayToGo(dir)){
            return move(dir);
        }else if(dir == firstDir && okayToGo(secondDir)){
            return move(secondDir);
        }else{
            return doNothing;
        }
    }

    public int moveRandomlyOneOfTheseDirectionsIfOpenOrElseDoNothing(direction firstDir, direction secondDir, direction thirdDir){

        boolean firstDirBad = false;
        boolean secondDirBad = false;
        boolean thirdDirBad = false;

        while(true){
            direction dir = pickRandomlyBetween(firstDir, secondDir, thirdDir);
            if(okayToGo(dir)){
                return move(dir);
            }
            if(dir == firstDir){
                firstDirBad = true;
            }
            if(dir == secondDir){
                secondDirBad = true;
            }
            if(dir == thirdDir){
                thirdDirBad = true;
            }
            if(firstDirBad && secondDirBad && thirdDirBad){
                return doNothing;
            }
        }
    }

    public int moveRandomlyOneOfTheseDirectionsIfOpenOrElseDoNothing(direction firstDir, direction secondDir, direction thirdDir, direction fourthDir){

        boolean firstDirBad = false;
        boolean secondDirBad = false;
        boolean thirdDirBad = false;
        boolean fourthDirBad = false;

        while(true){
            direction dir = pickRandomlyBetween(firstDir, secondDir, thirdDir, fourthDir);
            if(okayToGo(dir)){
                return move(dir);
            }
            if(dir == firstDir){
                firstDirBad = true;
            }
            if(dir == secondDir){
                secondDirBad = true;
            }
            if(dir == thirdDir){
                thirdDirBad = true;
            }
            if(dir == fourthDir){
                fourthDirBad = true;
            }
            if(firstDirBad && secondDirBad && thirdDirBad && fourthDirBad){
                return doNothing;
            }
        }
    }

    public direction pickRandomlyBetween(direction firstDir, direction secondDir){
        direction dir = direction.DONOTHING;

        int num = randomInt(1, 2);
        return (num == 1) ? (firstDir) : (secondDir);
    }

    public direction pickRandomlyBetween(direction firstDir, direction secondDir, direction thirdDir){
        direction dir = direction.DONOTHING;

        int num = randomInt(1, 3);
        switch(num){
            case 1:
                return firstDir;
            case 2:
                return secondDir;
            case 3:
                return thirdDir;
        }
        return dir;
    }

    public direction pickRandomlyBetween(direction firstDir, direction secondDir, direction thirdDir, direction fourthDir){
        direction dir = direction.DONOTHING;

        int num = randomInt(1, 4);

        switch(num){
            case 1:
                return firstDir;
            case 2:
                return secondDir;
            case 3:
                return thirdDir;
            case 4:
                return fourthDir;
        }
        return dir;
    }

    public int pickRandomlyBetweenAndMove(direction firstDir, direction secondDir, direction thirdDir, direction fourthDir){
        direction dir = pickRandomlyBetween(firstDir, secondDir, thirdDir, fourthDir);
        return move(dir);
    }

    public int pickRandomlyBetweenAndMove(direction firstDir, direction secondDir){
        direction dir = pickRandomlyBetween(firstDir, secondDir);
        return move(dir);
    }

    public int randomInt(int min, int max){
        rand = new Random();
        return rand.nextInt((max - min) + 1) + min;
    }

    public int pickRandomlyBetweenDirectionsAndMove(ArrayList<direction> directions){
        direction dir = direction.DONOTHING;

        int num = randomInt(1, directions.size());
        for(int i = 0; i < directions.size(); i++){
            if(num == i){
                dir = directions.get(i);
                break;
            }
        }
        return move(dir);
    }

    public int moveToOneOfLeastVisitedSquares(){
        int whatToDo = pickRandomlyBetweenDirectionsAndMove(getLeastVisitedSurroundingSquares());
        return whatToDo;
    }

    public ArrayList<direction> freeDirections(){
        ArrayList<direction> freeDirections = new ArrayList<direction>();
        if(okayToGoNorth()){
            freeDirections.add(direction.NORTH);
        }
        if(okayToGoEast()) {
            freeDirections.add(direction.EAST);
        }
        if(okayToGoSouth()) {
            freeDirections.add(direction.SOUTH);
        }
        if(okayToGoWest()){
            freeDirections.add(direction.WEST);
        }
        return freeDirections;
    }

    public boolean directionsOkay(direction firstDirection, direction secondDirection){
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
            if(getDirectionFromAgentAction(getXMovesBack(4)).ordinal() == d) {
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
        }else if (getLastMove() == moveEast && okayToGoWest()){
            return moveWest();
        }else if (getLastMove() == moveWest && okayToGoEast()){
            return moveEast();
        }else{
            return doNothing;
        }
    }

    public int plantMine(){
        changeMyPosition(me.position, me.position);  //I'm not moving, but call this function for bookkeeping.
        setMapSquare(me.position, 'm');
        me.movesMade.add(plantMine);
        possibleMines.add(me.position);
        return plantMine;
    }

    public int moveNorth(){
        Coordinate newPosition = new Coordinate(me.position.x, me.position.y - 1);
        changeMyPosition(me.position, newPosition);
        me.movesMade.add(moveNorth);
        return moveNorth;
    }

    public int moveEast(){
        Coordinate newPosition = new Coordinate(me.position.x + 1, me.position.y);
        changeMyPosition(me.position, newPosition);
        me.movesMade.add(moveEast);
        return moveEast;
    }

    public int moveSouth(){
        Coordinate newPosition = new Coordinate(me.position.x, me.position.y + 1);
        changeMyPosition(me.position, newPosition);
        me.movesMade.add(moveSouth);
        return moveSouth;
    }

    public int moveWest(){
        Coordinate newPosition = new Coordinate(me.position.x - 1, me.position.y);
        changeMyPosition(me.position, newPosition);
        me.movesMade.add(moveWest);
        return moveWest;
    }

    public int preferInOrder(direction firstDirection, direction secondDirection) {
        int whatToDo = doNothing;
        if (okayToGo(firstDirection)) {
            whatToDo = move(firstDirection);
        } else if (okayToGo(secondDirection)) {
            whatToDo = move(secondDirection);
        }
        return whatToDo;
    }

    public int preferInOrder(direction firstDirection, direction secondDirection, direction thirdDirection, direction fourthDirection){
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

        obstNorthEastSouth = (obstNorth && obstEast && obstSouth);
        obstEastSouthWest = (obstEast && obstSouth && obstWest);
        obstSouthWestNorth = (obstSouth && obstWest && obstNorth);
        obstWestNorthEast = (obstWest && obstNorth && obstEast);
        obstEveryDirection = (obstWest && obstNorth && obstEast && obstSouth);

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

        //if(obstInThreeDirections()){map[me.position.x][me.position.y] = 'X';}
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
                    makeEmptyTimesVisited();
                    return true;
                }
                if ((enemyBaseWest == false) && (me.spawn.x == 0) && (me.spawn.y == 0)) {
                    System.out.println("agent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                    changeMyPosition(me.position, me.spawn);
                    makeEmptyTimesVisited();
                    return true;
                }
            } else if ((ourBaseNorth == true) && (obstSouth == true)) {
                if ((enemyBaseWest == true) && (me.spawn.x == mapHeight - 1) && (me.spawn.y == mapHeight - 1)) {
                    System.out.println("agent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                    changeMyPosition(me.position, me.spawn);
                    makeEmptyTimesVisited();
                    return true;
                }
                if ((enemyBaseWest == false) && (me.spawn.x == 0) && (me.spawn.y == mapHeight - 1)) {
                    System.out.println("agent" + me.number + " has been respawned at (" + me.spawn.x + ", " + me.spawn.y + ")");
                    changeMyPosition(me.position, me.spawn);
                    makeEmptyTimesVisited();
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

    public void determineDefenseWallCenterPositionAndDirection(){

        if(enemyBaseWest){
            defenseWallCenter.position.x = ourBase.position.x - 2;
        }else{
            defenseWallCenter.position.x = ourBase.position.x + 2;
        }
        defenseWallCenter.position.y = ourBase.position.y;
        System.out.println("determined defense wall center " + defenseWallCenter.position.toString());

        if(positionIsNorthEast(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.NORTHEAST;
        }else if(positionIsNorthWest(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.NORTHWEST;
        }else if(positionIsSouthEast(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.SOUTHEAST;
        }else if(positionIsSouthWest(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.SOUTHWEST;
        }else if(positionIsNorth(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.NORTH;
        }else if(positionIsEast(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.EAST;
        }else if(positionIsSouth(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.SOUTH;
        }else{
            defenseWallCenter.dir = direction.WEST;
        }
    }

    public void setMapSquare(Coordinate pos, char c) {
        map[pos.x][pos.y] = c;
    }

    public void moveMeOnMap(Coordinate source, Coordinate destination) {
        if(obstInThreeDirections()){
            setMapSquare(source, 'X');
        }else {
            setMapSquare(source, ' ');
        }
        setMapSquare(destination, me.name);
    }

    public void updateTimesVisited(Coordinate pos){
        timesVisited[pos.x][pos.y]++;
    }

    public void changeMyPosition(Coordinate source, Coordinate destination) {
        me.squaresTravelled.add(new Coordinate(destination));
        updateTimesVisited(destination);
        moveMeOnMap(source, destination);
        me.position.set(destination);
    }

    public void makeEmptyMap() {
        map = new char[mapHeight][mapHeight];
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapHeight; j++) {
                map[i][j] = '.';
            }
        }
    }

    public void makeEmptyTimesVisited(){
        timesVisited = new int[mapHeight][mapHeight];
        for(int i = 0; i < mapHeight; i++){
            for(int j = 0; j < mapHeight; j++){
                timesVisited[i][j] = 0;
            }
        }
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
        Coordinate oneNorth = new Coordinate(me.position.x, me.position.y - 1);
        boolean hasPossibleMine = possibleMines.contains(oneNorth);
        return ((me.hasFlag && enemyNorthImmediate) || friendlyNorthImmediate || obstNorth || (ourBaseNorthImmediate && !me.hasFlag) || hasPossibleMine) ? (false) : (true);
    }

    public boolean okayToGoEast() {
        Coordinate oneEast = new Coordinate(me.position.x + 1, me.position.y);
        boolean hasPossibleMine = possibleMines.contains(oneEast);
        return ((me.hasFlag && enemyEastImmediate) || friendlyEastImmediate || obstEast || (ourBaseEastImmediate && !me.hasFlag) || hasPossibleMine) ? (false) : (true);
    }

    public boolean okayToGoWest() {
        Coordinate oneWest = new Coordinate(me.position.x - 1, me.position.y);
        boolean hasPossibleMine = possibleMines.contains(oneWest);
        return ((me.hasFlag && enemyWestImmediate)|| friendlyWestImmediate || obstWest || (ourBaseWestImmediate && !me.hasFlag) || hasPossibleMine) ? (false) : (true);
    }

    public boolean okayToGoSouth() {
        Coordinate oneSouth = new Coordinate(me.position.x, me.position.y + 1);
        boolean hasPossibleMine = possibleMines.contains(oneSouth);
        return ((me.hasFlag && enemySouthImmediate) || friendlySouthImmediate || obstSouth || (ourBaseSouthImmediate && !me.hasFlag) || hasPossibleMine) ? (false) : (true);
    }

    public void queryEnvironment(AgentEnvironment inEnvironment) {

        //do I currently have the flag
        me.hasFlag = inEnvironment.hasFlag();
        enemyHasOurFlag = inEnvironment.hasFlag(inEnvironment.ENEMY_TEAM);

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

        obstNorthEast = (obstNorth && obstEast);
        obstSouthEast = (obstSouth && obstEast);
        obstNorthWest = (obstNorth && obstWest);
        obstSouthWest = (obstSouth && obstWest);

        //immediate presence of enemy
        enemyNorthImmediate = inEnvironment.isAgentNorth(inEnvironment.ENEMY_TEAM, true);
        enemyEastImmediate = inEnvironment.isAgentEast(inEnvironment.ENEMY_TEAM, true);
        enemySouthImmediate = inEnvironment.isAgentSouth(inEnvironment.ENEMY_TEAM, true);
        enemyWestImmediate = inEnvironment.isAgentWest(inEnvironment.ENEMY_TEAM, true);

        //immediate presence of friendly agent
        friendlyNorthImmediate = inEnvironment.isAgentNorth(inEnvironment.OUR_TEAM, true);
        friendlyEastImmediate = inEnvironment.isAgentEast(inEnvironment.OUR_TEAM, true);
        friendlySouthImmediate = inEnvironment.isAgentSouth(inEnvironment.OUR_TEAM, true);
        friendlyWestImmediate = inEnvironment.isAgentWest(inEnvironment.OUR_TEAM, true);

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

    public boolean obstInThreeDirections() {
        return (obstNorthEastSouth || obstEastSouthWest || obstSouthWestNorth || obstWestNorthEast);
    }

    public boolean blockedInThreeDirections(){
        return (blockedEastSouthWest() || blockedNorthEastSouth() || blockedSouthWestNorth() || blockedSouthWestNorth());
    }

    public boolean blockedNorthEastSouth(){
        return (!okayToGoNorth() && !okayToGoEast() && !okayToGoSouth());
    }

    public boolean blockedEastSouthWest(){
        return (!okayToGoEast() && !okayToGoSouth() && !okayToGoWest());
    }

    public boolean blockedSouthWestNorth(){
        return (!okayToGoSouth() && !okayToGoWest() && !okayToGoNorth());
    }

    public boolean blockedWestNorthEast(){
        return (!okayToGoWest() && !okayToGoNorth() && !okayToGoEast());
    }

    public direction getOnlyNonObstDirection() {
        direction freeDirection = direction.EAST;
        if (obstNorthEastSouth) {
            freeDirection = direction.WEST;
        } else if (obstEastSouthWest) {
            freeDirection = direction.NORTH;
        } else if (obstSouthWestNorth) {
            freeDirection = direction.EAST;
        } else if (obstWestNorthEast) {
            freeDirection = direction.SOUTH;
        }
        return freeDirection;
    }

    public direction getOnlyFreeDirection() {
        direction freeDirection = direction.DONOTHING;
        if (blockedNorthEastSouth()) {
            freeDirection = direction.WEST;
        } else if (blockedEastSouthWest()) {
            freeDirection = direction.NORTH;
        } else if (blockedSouthWestNorth()) {
            freeDirection = direction.EAST;
        } else if (blockedWestNorthEast()) {
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