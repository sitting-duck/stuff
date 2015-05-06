package ctf.agent;

import java.util.Collections;
import java.util.Comparator;
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

    class AStarSearch {

        public ArrayList<Tile> queue = new ArrayList<Tile>();
        public ArrayList<Tile> visitedTiles = new ArrayList<Tile>();
        public ArrayList<ArrayList<Tile>> possibleSolutions = new ArrayList<ArrayList<Tile>>();

        public ArrayList<Coordinate> open = new ArrayList<Coordinate>();
        public ArrayList<Coordinate> closed = new ArrayList<Coordinate>();

        AStarSearch() {
        }
    }

    class Tile implements Comparator<Tile> {
        public Tile(){
            parent = null;
            position = new Coordinate();
            g = -1;
            h = -1;
            score = -1;
        }
        public Tile(Tile otherTile){
            parent = otherTile.parent;
            position = otherTile.position;
            g = otherTile.g;
            h = otherTile.h;
            score = otherTile.score;
        }

        Tile parent;
        Coordinate position;
        Integer g;
        Integer h;
        Integer score;

        public int compare(Tile first, Tile second){
            if(first.score < second.score){
                return -1;
            }else if(first.score == second.score){
                return 0;
            }else{
                return 1;
            }
        }
    }

    class PossibleSolution implements Comparator<ArrayList<Tile>>{
        public int compare(ArrayList<Tile> first, ArrayList<Tile> second){
            if(first.size() < second.size()){
                return -1;
            }else if (first.size() == second.size()){
                return 0;
            }else{
                return 1;
            }
        }
    }

    public ArrayList<Coordinate> getWalkableKnownCoordinatesAdjacentTo(Coordinate position){
        ArrayList<Coordinate> adjacentCoordinates = new ArrayList<Coordinate>();
        Coordinate oneNorth = position.oneNorth();
        Coordinate oneEast = position.oneEast();
        Coordinate oneSouth = position.oneSouth();
        Coordinate oneWest = position.oneWest();

        if(isInList(astar.open, oneNorth)){
            adjacentCoordinates.add(oneNorth);
        }
        if(isInList(astar.open, oneEast)){
            adjacentCoordinates.add(oneEast);
        }
        if(isInList(astar.open, oneSouth)){
            adjacentCoordinates.add(oneSouth);
        }
        if(isInList(astar.open, oneWest)){
            adjacentCoordinates.add(oneWest);
        }
        return adjacentCoordinates;
    }

        public ArrayList<Coordinate> getWalkableCoordinatesAdjacentToMyPosition(){
            ArrayList<Coordinate> adjacentTiles = new ArrayList<Coordinate>();
            Coordinate oneNorth = me.position.oneNorth();
            Coordinate oneEast = me.position.oneEast();
            Coordinate oneSouth = me.position.oneSouth();
            Coordinate oneWest = me.position.oneWest();

            if(okayToGoNorth()){
                adjacentTiles.add(oneNorth);
            }
            if(okayToGoEast()){
                adjacentTiles.add(oneEast);
            }
            if(okayToGoSouth()){
                adjacentTiles.add(oneSouth);
            }
            if(okayToGoWest()){
                adjacentTiles.add(oneWest);
            }
            return adjacentTiles;
        }

        public void addToQueue(ArrayList<Tile> list){
            for(int i = 0; i < list.size(); i++){
                astar.queue.add(new Tile(list.get(i)));
            }
        }

    //astar functions which for some reason work only out side the class def :/

    public ArrayList<Coordinate> shortestPath(Coordinate source, Coordinate destination){

        ArrayList<Tile> adjacentTiles;
        //ArrayList<Coordinate> adjacentToDestination = getWalkableKnownCoordinatesAdjacentTo(destination);
        //ArrayList<Tile> possibleSolution = new ArrayList<Tile>();
        Tile currentTile = initialTile(source, destination);

        //make sure that the enemy base and our base positions are visible to the search algo
        if(!isInList(astar.open, ourBase.position)){
            astar.open.add(ourBase.position);
        }
        if(!isInList(astar.open, enemyBase.position)){
            astar.open.add(enemyBase.position);
        }

        //the initial tile has been visited so add it
        astar.visitedTiles.add(currentTile);
        makeEmptyAstarMap();

        for(int i = 0; ; i++){

            //check to see if the current position is the goal position
            if(currentTile.position.isEqualTo(destination)){
                //then we have found a solution, add it to the list of possible solutions
                astar.possibleSolutions.add(solutionPathFromNode(currentTile));
            }

            expand(currentTile, destination);

            if(astar.queue.size() != 0){
                Collections.sort(astar.queue, new Tile());
                currentTile = astar.queue.get(0);
                astar.queue.remove(0);
                astarmap[currentTile.position.y][currentTile.position.x] = '?';
                printAStarMap();
            }else{

                //queue is empty, there is nothing else to search
                break;
            }
        }
        if(astar.possibleSolutions.size() != 0){
            //there was a solution
            ArrayList<Coordinate> shortestPath = chooseBestSolution();
            return shortestPath;
        }else{
            return new ArrayList<Coordinate>();
        }

    }

    public ArrayList<Coordinate> chooseBestSolution(){

        //first we are going to sort possibleSolutions by size (size is num tiles travelled)
        Collections.sort(astar.possibleSolutions, new PossibleSolution());
        ArrayList<Coordinate> solution = new ArrayList<Coordinate>();
        for(int i = 0; i < astar.possibleSolutions.get(0).size(); i++){
            solution.add(new Coordinate(astar.possibleSolutions.get(0).get(i).position));
        }
        return solution;
    }

    public ArrayList<Tile> solutionPathFromNode(Tile tile){
        ArrayList<Tile> possibleSolution = new ArrayList<Tile>();
        possibleSolution.add(tile);
        while(true){
            tile = tile.parent;
            if(tile == null){
                break;
            }else{
                possibleSolution.add(tile);
            }
        }
        return possibleSolution;
    }

    public boolean isInTileList(ArrayList<Tile> list, Tile tile){
        for(int i = 0; i < list.size(); i++){
            if(tile.position.isEqualTo(list.get(i).position)){
                return true;
            }
        }
        return false;
    }

    public void expand(Tile currentTile, Coordinate destination){

        //generate the child nodes of the current node and if they haven't been visited yet, place them in the queue
        ArrayList<Tile> adjacentTiles = getWalkableKnownTilesAdjacentTo(currentTile, destination);

        for(int i = 0; i < adjacentTiles.size(); i++){
            if(!isInTileList(astar.visitedTiles, adjacentTiles.get(i))){
                astar.visitedTiles.add(adjacentTiles.get(i));
                astar.queue.add(adjacentTiles.get(i));
            }
        }
    }

    public ArrayList<Tile> getWalkableKnownTilesAdjacentTo(Tile currentTile, Coordinate destination){
        ArrayList<Coordinate> adjacentCoordinates = getWalkableKnownCoordinatesAdjacentTo(currentTile.position);
        ArrayList<Tile> adjacentTiles = adjacentCoordinatesToTiles(currentTile, adjacentCoordinates, destination);
        return adjacentTiles;
    }

    public Tile initialTile(Coordinate coordinate, Coordinate destination){
        Tile newTile = new Tile();
        newTile.position = coordinate;
        newTile.g = 0;
        newTile.h = manhattanDistance(coordinate, destination);
        newTile.score = newTile.g + newTile.h;
        return newTile;
    }

    public ArrayList<Tile> adjacentCoordinatesToTiles(Tile parentTile, ArrayList<Coordinate> list, Coordinate destination){
        ArrayList<Tile> adjacentTiles = new ArrayList<Tile>();
        for(int i = 0; i < list.size(); i++){
            Tile newTile = new Tile();
            newTile.parent = parentTile;
            newTile.position = list.get(i);
            newTile.g = parentTile.g + 1;
            newTile.h = manhattanDistance(newTile.position, destination);
            newTile.score = newTile.g + newTile.h;
            adjacentTiles.add(newTile);
        }
        return adjacentTiles;
    }

    public ArrayList<Coordinate> tilesToCoordinates(ArrayList<Tile> list){
        ArrayList<Coordinate> coordinates = new ArrayList<Coordinate>();
        for(int i = 0; i < list.size(); i++){
            Coordinate newCoordinate = new Coordinate(list.get(i).position);
            coordinates.add(newCoordinate);
        }
        return coordinates;
    }

    public int compareTileByScore(Tile first, Tile second){
        if(first.score > second.score){
            return -1;
        }else if(first.score == second.score){
            return 0;
        }else{
            return 1;
        }
    }

    public AStarSearch addToOpenList(Coordinate position){
        if(!astar.open.contains(position)){
            astar.open.add(position);
        }
        return astar;
    }

    public AStarSearch addToClosedList(Coordinate position){
        if(!astar.closed.contains(position)){
            astar.closed.add(position);
        }
        return astar;
    }

    public boolean isWalkable(Coordinate position){
        return false;
    }

    public int computeScore(Coordinate squareToBeScored, Coordinate source, Coordinate destination){
        return 0;
    }

    enum obstacle {NONE, NORTH_WALL, EAST_WALL, SOUTH_WALL, WEST_WALL}

    private class Agent {
        public Integer number;
        public char name;
        public ArrayList<objective> objectives;
        public ArrayList<direction> directionsToGo;
        public ArrayList<obstacle> obstacles;
        public Coordinate spawn;
        public Coordinate position;
        public ArrayList<Coordinate> squaresTravelled;
        public ArrayList<Integer> movesMade;
        public boolean hasFlag;

        public Agent() {
            number = -1;
            objectives = new ArrayList<objective>();
            pushObjective(objective.INITIALIZE);
            directionsToGo = new ArrayList<direction>();
            obstacles = new ArrayList<obstacle>();
            
            spawn = new Coordinate();
            position = new Coordinate();
            squaresTravelled = new ArrayList<Coordinate>();
            movesMade = new ArrayList<Integer>();
            hasFlag = false;
        }

        public int getLastMoveMade() {
            return movesMade.get(movesMade.size() - 1);
        }

        public int getXMovesMadeBack(int x){
            return movesMade.get((movesMade.size() - 1) - x);
        }

        public int getLastNonDirMove(direction dir){
            int moveNumber = 1;
            int move = getAgentActionFromDirection(dir);
            while(getXMovesMadeBack(moveNumber) == move){
                moveNumber++;
            }
            return getXMovesMadeBack(moveNumber);
        }

        public int getLastNonDirMove(direction firstDir, direction secondDir){
            int moveNumber = 1;
            int firstMove = getAgentActionFromDirection(firstDir);
            int secondMove = getAgentActionFromDirection(secondDir);
            while(getXMovesMadeBack(moveNumber) == firstMove || getXMovesMadeBack(moveNumber) == secondMove){
                moveNumber++;
            }
            return getXMovesMadeBack(moveNumber);
        }

        public Agent pushMoveMade(int newMove) {
            movesMade.add(newMove);
            return this;
        }

        public Agent popMoveMade() {
            movesMade.remove(movesMade.size() - 1);
            return this;
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

        public objective getCurrentObjective() {
            return objectives.get(objectives.size() - 1);
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

        public objective getXObjectivesBack(int x) {
            return objectives.get((objectives.size() - 1) - x);
        }

        public direction getCurrentDirectionToGo() {
            return directionsToGo.get(directionsToGo.size() - 1);
        }

        public Agent setNewCurrentDirection(direction newDirection) {
            popDirectionToGo();
            pushDirectionToGo(newDirection);
            return this;
        }

        public Agent setNewBaseDirection(direction newDirection){
            directionsToGo.set(0, newDirection);
            return this;
        }

        public direction getBaseDirection(){
            return directionsToGo.get(0);
        }

        public Agent pushDirectionToGo(direction newDirection) {
            directionsToGo.add(newDirection);
            return this;
        }

        public Agent popDirectionToGo() {
            directionsToGo.remove(directionsToGo.size() - 1);
            return this;
        }

        public direction getXDirectionsBack(int x) {
            return directionsToGo.get((directionsToGo.size() - 1) - x);
        }

        public String getCurrentObstacleString(){

            String obstacleString = "";

            switch(getCurrentObstacle()){
                case NONE:
                    obstacleString = "none";
                    break;
                case NORTH_WALL:
                    obstacleString = "NORTH_WALL";
                    break;
                case EAST_WALL:
                    obstacleString = "EAST_WALL";
                    break;
                case SOUTH_WALL:
                    obstacleString = "SOUTH_WALL";
                    break;
                case WEST_WALL:
                    obstacleString = "WEST_WALL";
                    break;
            }
            return obstacleString;
        }

        public obstacle getCurrentObstacle() {
            return obstacles.get(obstacles.size() - 1);
        }

        public Agent setNewCurrentObjective(obstacle newObstacle) {
            popObstacle();
            pushObstacle(newObstacle);
            return this;
        }

        public Agent setNewBaseObstacle(obstacle newObstacle){
            obstacles.set(0, newObstacle);
            return this;
        }

        public obstacle getBaseObstacle(){
            return obstacles.get(0);
        }

        public Agent pushObstacle(obstacle newObstacle) {
            obstacles.add(newObstacle);
            return this;
        }

        public Agent popObstacle() {
            obstacles.remove(obstacles.size() - 1);
            return this;
        }

        public Agent clearObstacles(){
            obstacles.clear();
            return this;
        }

        public Agent removeObstacleInDirection(direction dir){
            for(int i = 0; i < obstacles.size(); i++){
                if(obstacles.get(i) == getObstacleDirectionFromDirection(dir)){
                    obstacles.remove(i);
                }
            }
            return this;
        }

        public objective getXObstaclesBack(int x) {
            return objectives.get((objectives.size() - 1) - x);
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

        public Coordinate one(direction dir){
            switch(dir){
                case NORTH:
                    return oneNorth();
                case EAST:
                    return oneEast();
                case SOUTH:
                    return oneSouth();
                case WEST:
                    return oneWest();
                default:
                    return this.position;
            }
        }

        public Coordinate one_safe(direction dir){
            switch(dir){
                case NORTH:
                    return oneNorth_Safe();
                case EAST:
                    return oneEast_Safe();
                case SOUTH:
                    return oneSouth_Safe();
                case WEST:
                    return oneWest_Safe();
                default:
                    return this.position;
            }
        }

        public Coordinate oneNorth_Safe() {
            return position.oneNorth_Safe();
        }

        public Coordinate oneEast_Safe() {
            return position.oneEast_Safe();
        }

        public Coordinate oneSouth_Safe() {
            return position.oneSouth_Safe();
        }

        public Coordinate oneWest_Safe() {
            return position.oneWest_Safe();
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

        public boolean equals(Coordinate otherCoordinate){
            return ((this.x == otherCoordinate.x) && (this.y == otherCoordinate.y));
        }

        public Coordinate one(direction dir){
            switch(dir){
                case NORTH:
                    return oneNorth();
                case EAST:
                    return oneEast();
                case SOUTH:
                    return oneSouth();
                case WEST:
                    return oneWest();
                default:
                    return this;
            }
        }

        public Coordinate one_Safe(direction dir){
            switch(dir){
                case NORTH:
                    return oneNorth_Safe();
                case EAST:
                    return oneEast_Safe();
                case SOUTH:
                    return oneSouth_Safe();
                case WEST:
                    return oneWest_Safe();
                default:
                    return this;
            }
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

        public Coordinate oneNorth_Safe(){
            if(this.y == 0){
                return new Coordinate(this.x, this.y);
            }else{
                return new Coordinate(this.x, this.y - 1);
            }
        }

        public Coordinate oneSouth_Safe(){
            if(this.y == mapHeight){
                return new Coordinate(x, y);
            }else{
                return new Coordinate(x, y + 1);
            }
        }

        public Coordinate oneEast_Safe(){
            if(this.x == mapHeight){
                return new Coordinate(x, y);
            }else{
                return new Coordinate(x + 1, y);
            }
        }

        public Coordinate oneWest_Safe(){
            if(this.x == 0){
                return new Coordinate(x, y);
            }else{
                return new Coordinate(x - 1, y);
            }
        }
    }

    //Agents
    private final static int MAX_NUM_AGENTS = 2;
    private static ArrayList<Agent> agents = new ArrayList<Agent>();
    private Agent me;
    private Agent otherAgent;

    private enum objective {INITIALIZE, SEEK_ENEMY_BASE, SEEK_ENEMY_BASE_VIA_KNOWN_SHORTEST_PATH,  SEEK_OUR_BASE, SEEK_OUR_BASE_VIA_KNOWN_SHORTEST_PATH, RETRIEVE_FRIENDLY_FLAG, DEFEND_OUR_BASE, MOVE_AROUND_OBSTACLE}


    //Map
    private static char[][] map;
    private static int[][] timesVisited;
    private int mapHeight = 10;         //it is known that mapHeight == mapLength
    private Place ourBase;
    private Place enemyBase;
    private Place seekPoint;
    private Place defenseWallCenter;
    private ArrayList<Place> pointsOfInterest;
    private ArrayList<Coordinate> possibleMines = new ArrayList<Coordinate>();

    private enum direction {NORTH, EAST, SOUTH, WEST, SOUTHWEST, SOUTHEAST, NORTHEAST, NORTHWEST, DONOTHING}

    //Strategy
    boolean oneDefenderOneOffender = false;

    private static char[][] astarmap;


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

    private static boolean enemyBaseFound = false;
    private static boolean ourBaseFound = false;
    private static ArrayList<Coordinate> shortestPathFromOurBaseToEnemyBase = new ArrayList<Coordinate>();
    private static AStarSearch astar;

    Random rand;


    public Tharpoon5() {

        //Agent
        if (agents.size() == MAX_NUM_AGENTS) {
            agents.clear();
            enemyBaseFound = false;
            ourBaseFound = false;
            shortestPathFromOurBaseToEnemyBase.clear();
            astar = new AStarSearch();
            shortestPathFromOurBaseToEnemyBase.clear();
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
        pointsOfInterest = new ArrayList<Place>();
        pointsOfInterest.add(ourBase);
        pointsOfInterest.add(enemyBase);
        pointsOfInterest.add(defenseWallCenter);

        astar = new AStarSearch();
    }

    public int getMove(AgentEnvironment inEnvironment) {

        int whatToDo = doNothing;

        //init
        queryEnvironment(inEnvironment);

        //some initilizations before we start seeking
        if (me.getCurrentObjective() == objective.INITIALIZE) {
            determineMySpawnAndInitialPosition();
            determineBasePositions();
        }

        amIAtSpawn();
        addSurroundingObstaclesToMap(inEnvironment);
        checkForPresenceOfBase();

        if (me.hasFlag) {
            me.setNewBaseObjective(objective.SEEK_OUR_BASE);
        }else{
            me.setNewBaseObjective(objective.SEEK_ENEMY_BASE);
        }

        //in the case that we have found the shortest path, we will create a seekpoint to get on the path, and then
        //we will follow that path
        if(enemyBaseFound && ourBaseFound){

            shortestPathFromOurBaseToEnemyBase = shortestPath(getPointOfInterestByName("ourBase").position, getPointOfInterestByName("enemyBase").position);

            if(shortestPathFromOurBaseToEnemyBase.size() != 0){
                seekPoint = new Place("seekPoint");
                seekPoint.position = closestToPositionFromList(me.position, shortestPathFromOurBaseToEnemyBase);
                seekPoint.dir = getDirectionOfPointRelativeToMe(seekPoint.position);
            }
            if(me.hasFlag && shortestPathFromOurBaseToEnemyBase.size() != 0){
                if(IAmOnShortestPath()){
                    me.objectives.clear();
                    me.pushObjective(objective.SEEK_OUR_BASE_VIA_KNOWN_SHORTEST_PATH);
                }else{
                    me.setNewBaseObjective(objective.SEEK_OUR_BASE_VIA_KNOWN_SHORTEST_PATH);
                }
            }else if(!me.hasFlag && shortestPathFromOurBaseToEnemyBase.size() != 0){
                if(IAmOnShortestPath()){
                    me.objectives.clear();
                    me.pushObjective(objective.SEEK_ENEMY_BASE_VIA_KNOWN_SHORTEST_PATH);
                }else{
                    me.setNewBaseObjective(objective.SEEK_ENEMY_BASE_VIA_KNOWN_SHORTEST_PATH);
                }
            }
        }

        switch (me.getCurrentObjective()) {
            case SEEK_ENEMY_BASE:
                whatToDo = seek(getPointOfInterestByName("enemyBase"));
                break;
            case SEEK_ENEMY_BASE_VIA_KNOWN_SHORTEST_PATH:
                if(!IAmOnShortestPath()){
                    whatToDo = seek(seekPoint);
                }else{
                    if(me.position.isEqualTo(enemyBase.position)){
                        //we are already at the enemy base
                        return doNothing;
                    }
                    int index = getIndexOfPointInList(shortestPathFromOurBaseToEnemyBase, me.position);
                    Coordinate whereToGo = shortestPathFromOurBaseToEnemyBase.get(index - 1);
                    direction directionOfPointRelativeTome = getDirectionOfPointRelativeToMe(whereToGo);
                    if(okayToGo(directionOfPointRelativeTome)){
                        whatToDo = move(getDirectionOfPointRelativeToMe(whereToGo));
                    }else{
                        whatToDo = seek(getPointOfInterestByName("enemyBase"));
                    }
                }
                break;
            case SEEK_OUR_BASE:
                whatToDo = seek(getPointOfInterestByName("ourBase"));
                break;
            case SEEK_OUR_BASE_VIA_KNOWN_SHORTEST_PATH:
                if(!IAmOnShortestPath()){
                    whatToDo = seek(seekPoint);
                }else{
                    if(me.position.isEqualTo(ourBase.position)){
                        //we are already at our base
                        return doNothing;
                    }
                    int index = getIndexOfPointInList(shortestPathFromOurBaseToEnemyBase, me.position);
                    Coordinate whereToGo = shortestPathFromOurBaseToEnemyBase.get(index + 1);
                    direction directionOfPointRelativeTome = getDirectionOfPointRelativeToMe(whereToGo);
                    if(okayToGo(directionOfPointRelativeTome)){
                        whatToDo = move(getDirectionOfPointRelativeToMe(whereToGo));
                    }else{
                        whatToDo = seek(getPointOfInterestByName("ourBase"));
                    }
                }
                break;
            case DEFEND_OUR_BASE:
                whatToDo = defend(ourBase);
                break;
            case MOVE_AROUND_OBSTACLE:
                if(me.getBaseObjective() == objective.SEEK_OUR_BASE || me.getBaseObjective() == objective.SEEK_OUR_BASE_VIA_KNOWN_SHORTEST_PATH){
                    whatToDo = goAroundObstacle(ourBase);
                }else if(me.getBaseObjective() == objective.SEEK_ENEMY_BASE || me.getBaseObjective() == objective.SEEK_ENEMY_BASE_VIA_KNOWN_SHORTEST_PATH){
                    whatToDo = goAroundObstacle(enemyBase);
                }
        }

        //print only after every complete move (ie, both agents have moved)
        if (me.number == 1) {
            if(enemyBaseFound && ourBaseFound){
                printMapAndTimesVisitedWithShortestPath(shortestPathFromOurBaseToEnemyBase);
            }else{
                //printMap();
                printMapAndTimesVisited();
            }
        }

        return whatToDo;
    }

    public int seek(Place place) {

        int whatToDo = doNothing;
        System.out.println("agent " + me.name + " has obj " + me.getCurrentObjectiveString());

        //these two checks need to be separate because only in the case where there is an obstacle on three sides, will we put an x in that square
        if (obstInThreeDirections()) {
            whatToDo = move(getOnlyNonObstDirection());
            return whatToDo;
        }
        if(blockedInThreeDirections()){
            whatToDo = move(getOnlyFreeDirection());
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
                }else{
                    me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                    whatToDo = goAroundObstacle(place);
                }
                break;
            case NORTHEAST:
                if(okayToGoNorth() && okayToGoEast()){
                    //whatToDo = preferInOrder(direction.EAST, direction.NORTH);
                    whatToDo = pickRandomlyBetweenAndMove(direction.NORTH, direction.EAST);
                }else{
                    me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                    whatToDo = goAroundObstacle(place);
                }
                break;
            case NORTHWEST:
                if(okayToGoNorth() && okayToGoWest()){
                    whatToDo = pickRandomlyBetweenAndMove(direction.NORTH, direction.WEST);
                    //whatToDo = preferInOrder(direction.WEST, direction.NORTH);
                }else{
                    me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                    whatToDo = goAroundObstacle(place);
                 }
                break;
            case SOUTH:
                if(okayToGoSouth()){
                    whatToDo = moveSouth();
                }else{
                    me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                    whatToDo = goAroundObstacle(place);
                }
                break;
            case SOUTHEAST:
                if(okayToGoSouth() && okayToGoEast()){
                    whatToDo = pickRandomlyBetweenAndMove(direction.SOUTH, direction.EAST);
                }else{
                    me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                    whatToDo = goAroundObstacle(place);
                }
                break;
            case SOUTHWEST:
                if(okayToGoSouth() && okayToGoWest()){
                    whatToDo = pickRandomlyBetweenAndMove(direction.SOUTH, direction.WEST);
                }else{
                    me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                    whatToDo = goAroundObstacle(place);
                }
                break;
            case EAST:
                if(okayToGoEast()){
                    whatToDo = moveEast();
                }else{
                    me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                    whatToDo = goAroundObstacle(place);
                }
                break;
            case WEST:
                if(okayToGoWest()){
                    whatToDo = moveWest();
                }else{
                    me.pushObjective(objective.MOVE_AROUND_OBSTACLE);
                    whatToDo = goAroundObstacle(place);
                }
                break;
        }
        System.out.println("agent " + me.name + " " + getNameFromAgentAction(whatToDo) + "to position " + me.position.toString());
        return whatToDo;
    }

    public Place getPointOfInterestByName(String name){
        for(int i = 0; i < pointsOfInterest.size(); i++){
            Place currentPointOfInterest = pointsOfInterest.get(i);
            if(currentPointOfInterest.name == name){
                return currentPointOfInterest;
            }
        }
        return new Place("none found");
    }

    public boolean IAmOnShortestPath(){
        return (isInList(shortestPathFromOurBaseToEnemyBase, me.position));
    }

    public void checkForPresenceOfBase(){
        if(ourBaseNorthImmediate || ourBaseEastImmediate || ourBaseSouthImmediate || ourBaseWestImmediate){
            ourBaseFound = true;
        }
        if(enemyBaseNorthImmediate || enemyBaseEastImmediate || enemyBaseSouthImmediate || enemyBaseWestImmediate){
            enemyBaseFound = true;
        }
    }

    public void determineDirectionToGoAroundObstacles(Place pointOfInterest){

        me.obstacles = new ArrayList<obstacle>(getSurroundingObstacles());

        //TUNNELS
        if(!okayToGoEast() && !okayToGoWest()){
            System.out.println("ew tunnel");
            direction nonEastOrWestDir;

           //if(me.hasFlag){
                nonEastOrWestDir = pickRandomlyBetween(direction.SOUTH, direction.NORTH);
            //}else{
                //if I don't have the flag, prefer less visited squares
            //    nonEastOrWestDir = getLeastVisitedFrom(direction.SOUTH, direction.NORTH);
            //}

            if(pointOfInterest.dir == direction.NORTHEAST) {
                me.pushDirectionToGo(direction.NORTH);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHEAST){
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(pointOfInterest.dir == direction.EAST){
                me.pushDirectionToGo(nonEastOrWestDir);
                return;
            }

            if(pointOfInterest.dir == direction.WEST){
                me.pushDirectionToGo(nonEastOrWestDir);
                return;
            }

            if(pointOfInterest.dir == direction.NORTHWEST){
                me.pushDirectionToGo(direction.NORTH);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHWEST){
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTH){
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(pointOfInterest.dir == direction.NORTH){
                me.pushDirectionToGo(direction.NORTH);
                return;
            }
        }

        if(!okayToGoNorth() && !okayToGoSouth()){
            System.out.println("ns tunnel");

            direction nonNorthOrSouthDir;
            //if(me.hasFlag){
                nonNorthOrSouthDir = pickRandomlyBetween(direction.EAST, direction.WEST);
            //}else{
                //if I don't have the flag, prefer less visited squares
            //    nonNorthOrSouthDir = getLeastVisitedFrom(direction.EAST, direction.WEST);
            //}

            if(pointOfInterest.dir == direction.NORTHEAST) {
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHEAST){
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            if(pointOfInterest.dir == direction.EAST){
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            if(pointOfInterest.dir == direction.WEST){
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if(pointOfInterest.dir == direction.NORTHWEST){
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHWEST){
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTH){
                me.pushDirectionToGo(nonNorthOrSouthDir);
                return;
            }

            if(pointOfInterest.dir == direction.NORTH){
                me.pushDirectionToGo(nonNorthOrSouthDir);
                return;
            }

        }

    //CORNERS
        //if obstEast and obstNorth
        if(!okayToGoEast() && !okayToGoNorth()){
            System.out.println("ne corner");

            direction nonNorthOrEastDir;
            //if(me.hasFlag){
                nonNorthOrEastDir = pickRandomlyBetween(direction.SOUTH, direction.WEST);
            //}else{
                //if I don't have the flag, prefer less visited squares
            //    nonNorthOrEastDir = getLeastVisitedFrom(direction.SOUTH, direction.WEST);
            //}

            if(pointOfInterest.dir == direction.NORTHEAST) {
                me.pushDirectionToGo(nonNorthOrEastDir);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHEAST){
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(pointOfInterest.dir == direction.EAST){
                me.pushDirectionToGo(nonNorthOrEastDir);
                return;
            }

            if(pointOfInterest.dir == direction.WEST){
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if(pointOfInterest.dir == direction.NORTHWEST){
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHWEST){
                me.pushDirectionToGo(nonNorthOrEastDir);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTH){
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(pointOfInterest.dir == direction.NORTH){
                me.pushDirectionToGo(nonNorthOrEastDir);
                return;
            }
        }

        //if obstEast and obstSouth
        if(!okayToGoEast() && !okayToGoSouth()) {
            System.out.println("se corner");

            direction nonSouthOrEastDir;
            //if(me.hasFlag){
                nonSouthOrEastDir = pickRandomlyBetween(direction.NORTH, direction.WEST);
            //}else{
                //if I don't have the flag, prefer less visited squares
            //    nonSouthOrEastDir = getLeastVisitedFrom(direction.NORTH, direction.WEST);
            //}

            if (pointOfInterest.dir == direction.NORTHEAST) {
                me.pushDirectionToGo(nonSouthOrEastDir);
                return;
            }

            if (pointOfInterest.dir == direction.SOUTHEAST) {
                me.pushDirectionToGo(nonSouthOrEastDir);
                return;
            }

            if (pointOfInterest.dir == direction.EAST) {
                me.pushDirectionToGo(nonSouthOrEastDir);
                return;
            }

            if (pointOfInterest.dir == direction.WEST) {
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if (pointOfInterest.dir == direction.NORTHWEST) {
                me.pushDirectionToGo(nonSouthOrEastDir);
                return;
            }

            if (pointOfInterest.dir == direction.SOUTHWEST) {
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if (pointOfInterest.dir == direction.NORTH) {
                me.pushDirectionToGo(direction.NORTH);
                return;
            }

            if (pointOfInterest.dir == direction.SOUTH) {
                me.pushDirectionToGo(nonSouthOrEastDir);
                return;
            }
        }

        //if obstWest and obstSouth
        if(!okayToGoWest() && !okayToGoSouth()){
            System.out.println("sw corner");

            direction nonSouthOrWestDir;
            //if(me.hasFlag){
                nonSouthOrWestDir = pickRandomlyBetween(direction.NORTH, direction.EAST);
            //}else{
                //if I don't have the flag, prefer less visited squares
            //    nonSouthOrWestDir = getLeastVisitedFrom(direction.NORTH, direction.EAST);
            //}

            if(pointOfInterest.dir == direction.NORTHEAST) {
                me.pushDirectionToGo(nonSouthOrWestDir);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHEAST){
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            if(pointOfInterest.dir == direction.EAST){
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            if(pointOfInterest.dir == direction.WEST){
                me.pushDirectionToGo(nonSouthOrWestDir);
                return;
            }

            if(pointOfInterest.dir == direction.NORTHWEST){
                me.pushDirectionToGo(direction.NORTH);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHWEST){
                me.pushDirectionToGo(nonSouthOrWestDir);
                return;
            }

            if(pointOfInterest.dir == direction.NORTH){
                me.pushDirectionToGo(direction.NORTH);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTH){
                me.pushDirectionToGo(nonSouthOrWestDir);
                return;
            }
        }

        //if obstWest and obstNorth
        if(!okayToGoWest() && !okayToGoNorth()){
            System.out.println("nw corner");

            direction nonNorthOrWestDir;
            //if(me.hasFlag){
                nonNorthOrWestDir = pickRandomlyBetween(direction.SOUTH, direction.EAST);
            //}else{
                //if I don't have the flag, prefer less visited squares
            //    nonNorthOrWestDir = getLeastVisitedFrom(direction.SOUTH, direction.EAST);
            //}

            if(pointOfInterest.dir == direction.NORTHEAST) {
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHEAST){
                me.pushDirectionToGo(nonNorthOrWestDir);
                return;
            }

            if(pointOfInterest.dir == direction.EAST){
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            if(pointOfInterest.dir == direction.WEST){
                me.pushDirectionToGo(nonNorthOrWestDir);
                return;
            }

            if(pointOfInterest.dir == direction.NORTHWEST){
                me.pushDirectionToGo(nonNorthOrWestDir);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTHWEST){
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(pointOfInterest.dir == direction.SOUTH){
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(pointOfInterest.dir == direction.NORTH){
                me.pushDirectionToGo(nonNorthOrWestDir);
                return;
            }
        }

        int numMovesBack = 1;

        //WALLS

        //EAST WALL//EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL //EAST WALL
        //if obstEast and objective is south or southeast, keep going south until obstSouth or !obstEast
        if(!okayToGoEast() && (pointOfInterest.dir == direction.SOUTH || pointOfInterest.dir == direction.SOUTHEAST)){
            System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.SOUTH) + " around east wall");
            me.pushDirectionToGo(direction.SOUTH);
            return;
        }

        //if obstEast and objective is north or northeast, keep going north until obstNorth or !obstEast
        if(!okayToGoEast() && (pointOfInterest.dir == direction.NORTH || pointOfInterest.dir == direction.NORTHEAST)){
            System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.NORTH) + " around east wall");
            me.pushDirectionToGo(direction.NORTH);
            return;
        }

        //if obstEast and objective is east,
        if(!okayToGoEast() && (pointOfInterest.dir == direction.EAST || pointOfInterest.dir == direction.WEST || pointOfInterest.dir == direction.SOUTHWEST || pointOfInterest.dir == direction.NORTHWEST)){

            direction nonEastDir;
            if(me.hasFlag){
                nonEastDir = pickRandomlyBetween(direction.SOUTH, direction.NORTH, direction.WEST);
            }else{
                //if I don't have the flag, prefer less visited squares
                nonEastDir = getLeastVisitedFrom(direction.SOUTH, direction.NORTH, direction.WEST);
            }

            if(nonEastDir == direction.NORTH){
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.NORTH) + " around east wall");
                me.pushDirectionToGo(direction.NORTH);
                return;
            }

            if(nonEastDir == direction.SOUTH) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.SOUTH) + " around east wall");
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(nonEastDir == direction.WEST) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.WEST) + " around east wall");
                me.pushDirectionToGo(direction.WEST);
                return;
            }
        }

        //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL //WEST WALL
        //if obstWest and objective is south or southwest, keep going south until obstSouth or !obstWest
        if(!okayToGoWest() && (pointOfInterest.dir == direction.SOUTH || pointOfInterest.dir == direction.SOUTHWEST)){
            System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.SOUTH) + " around west wall");
            me.pushDirectionToGo(direction.SOUTH);
            return;
        }

        //if obstWest and objective is north or northwest, keep going north until obstNorth or !obstWest
        if(!okayToGoWest() && (pointOfInterest.dir == direction.NORTH || pointOfInterest.dir == direction.NORTHWEST)){
            System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.NORTH) + " around west wall");
            me.pushDirectionToGo(direction.NORTH);
            return;
        }

        //if obstWest and objective is west,
        if(!okayToGoWest() && (pointOfInterest.dir == direction.WEST || pointOfInterest.dir == direction.EAST || pointOfInterest.dir == direction.SOUTHEAST || pointOfInterest.dir == direction.NORTHEAST)){

            direction nonWestDir;
            if(me.hasFlag){
                nonWestDir = pickRandomlyBetween(direction.SOUTH, direction.NORTH, direction.EAST);
            }else{
                //if I don't have the flag, prefer less visited squares
                nonWestDir = getLeastVisitedFrom(direction.SOUTH, direction.NORTH, direction.EAST);
            }

            //if last move was moveNorth keep going north until !obstWest or obstNorth
            if(nonWestDir == direction.NORTH) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.NORTH) + " around west wall");
                me.pushDirectionToGo(direction.NORTH);
                return;
            }

            //if last move was moveSouth keep going south until !obstWest or obstSouth
            if(nonWestDir == direction.SOUTH) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.SOUTH) + " around west wall");
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }

            if(nonWestDir == direction.EAST) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.EAST) + " around west wall");
                me.pushDirectionToGo(direction.EAST);
                return;
            }
        }

        //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL //NORTH WALL
        //if obstNorth and objective is east or northeast, keep going east until obstEast or !obstNorth
        if(!okayToGoNorth() && (pointOfInterest.dir == direction.EAST || pointOfInterest.dir == direction.NORTHEAST)){
            System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.EAST) + " around north wall");
            me.pushDirectionToGo(direction.EAST);
            return;
        }

        //if obstNorth and objective is west or northwest, keep going west until obstWest or !obstNorth
        if(!okayToGoNorth() && (pointOfInterest.dir == direction.WEST || pointOfInterest.dir == direction.NORTHWEST)){
            System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.WEST) + " around north wall");
            me.pushDirectionToGo(direction.WEST);
            return;
        }

        //if obstNorth and objective is north,
        if(!okayToGoNorth() && (pointOfInterest.dir == direction.NORTH || pointOfInterest.dir == direction.SOUTH || pointOfInterest.dir == direction.SOUTHWEST || pointOfInterest.dir == direction.SOUTHEAST)){

            direction nonNorthDir;
            if(me.hasFlag){
                nonNorthDir = pickRandomlyBetween(direction.EAST, direction.WEST, direction.SOUTH);
            }else{
                //if I don't have the flag, prefer less visited squares
                nonNorthDir = getLeastVisitedFrom(direction.EAST, direction.WEST, direction.SOUTH);
            }

            //if last move was moveEast keep going east until !obstNorth or obstEast
            if(nonNorthDir == direction.EAST) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.EAST) + " around north wall");
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            //if last move was moveWest keep going west until !obstNorth or obstWest
            if(nonNorthDir == direction.WEST) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.WEST) + " around north wall");
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if(nonNorthDir == direction.SOUTH) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.SOUTH) + " around north wall");
                me.pushDirectionToGo(direction.SOUTH);
                return;
            }
        }

        //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL //SOUTH WALL
        //if obstSouth and objective is east or southeast, keep going east until obstEast or !obstSouth
        if(!okayToGoSouth() && (pointOfInterest.dir == direction.EAST || pointOfInterest.dir == direction.SOUTHEAST)){
            System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.EAST) + " around south wall");
            me.pushDirectionToGo(direction.EAST);
            return;
        }

        //if obstSouth and objective is west or southwest, keep going west until obstWest or !obstSouth
        if(!okayToGoSouth() && (pointOfInterest.dir == direction.WEST || pointOfInterest.dir == direction.SOUTHWEST)){
            System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.WEST) + " around south wall");
            me.pushDirectionToGo(direction.WEST);
            return;
        }

        //if obstSouth and objective is south,
        if(!okayToGoSouth() && (pointOfInterest.dir == direction.SOUTH || pointOfInterest.dir == direction.NORTH || pointOfInterest.dir == direction.NORTHEAST || pointOfInterest.dir == direction.NORTHWEST)){

            direction nonSouthDir;
            if(me.hasFlag){
                nonSouthDir = pickRandomlyBetween(direction.EAST, direction.WEST, direction.NORTH);
            }else{
                //if I don't have the flag, prefer less visited squares
                nonSouthDir = getLeastVisitedFrom(direction.EAST, direction.WEST, direction.NORTH);
            }

            //if last move was moveEast keep going east until !obstSouth or obstEast
            if(nonSouthDir == direction.EAST) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.EAST) + " around south wall");
                me.pushDirectionToGo(direction.EAST);
                return;
            }

            //if last move was moveWest keep going west until !obstSouth or obstWest
            if(nonSouthDir == direction.WEST) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.WEST) + " around south wall");
                me.pushDirectionToGo(direction.WEST);
                return;
            }

            if(nonSouthDir == direction.NORTH) {
                System.out.println("agent " + me.name + me.number + " decided to go " + getDirectionName(direction.NORTH) + " around south wall");
                me.pushDirectionToGo(direction.NORTH);
                return;
            }
        }

        System.out.println("NOTHING WAS SET");
    }

    public ArrayList<obstacle> getSurroundingObstacles(){
        ArrayList<obstacle> obstacles = new ArrayList<obstacle>();
        if(!okayToGo(direction.NORTH)){
            obstacles.add(obstacle.NORTH_WALL);
        }
        if(!okayToGo(direction.EAST)){
            obstacles.add(obstacle.EAST_WALL);
        }
        if (!okayToGo(direction.SOUTH)){
            obstacles.add(obstacle.SOUTH_WALL);
        }
        if(!okayToGo(direction.WEST)) {
            obstacles.add(obstacle.WEST_WALL);
        }
        return obstacles;
    }

    public int goAroundObstacle(Place pointOfInterest){

        //case where we are blocked on three sides, there is only one way to go
        if(blockedInThreeDirections()){
            me.popObjective();
            me.popDirectionToGo();
            return move(getOnlyFreeDirection());
        }

        //if this is our first encounter with this obstacle, we choose a direction to go
        if(me.directionsToGo.size() == 0){
            determineDirectionToGoAroundObstacles(pointOfInterest);
        }

        //other wise we keep going in that direction until one of the obstacles surrounding us is gone
        direction currentDir = me.getCurrentDirectionToGo();

        if(anyObstaclesNoLongerPresent()){
            removeObstaclesNoLongerPresent();
        }
        //if there are actually no obstacles around us, go back to seek function
        if(me.obstacles.size() == 0){
            me.popDirectionToGo();
            me.popObjective();
            System.out.println("agent " + me.name + " got around obstacle");
            return seek(pointOfInterest);
        }
        if(okayToGo(currentDir)){
            return move(currentDir);
        }else{
            me.popDirectionToGo();
            return goAroundObstacle(pointOfInterest);
        }
    }

    public boolean anyObstaclesNoLongerPresent(){
        for(int i = 0; i < me.obstacles.size(); i++){
            if(okayToGo(getDirectionFromObstacleDirection(me.obstacles.get(i)))){
                return true;
            }
        }
        return false;
    }

    public void removeObstaclesNoLongerPresent(){
        ArrayList<Integer> obstaclesToRemove = new ArrayList<Integer>();
        for(int i = 0; i < me.obstacles.size(); i++){
            if(okayToGo(getDirectionFromObstacleDirection(me.obstacles.get(i)))){
                obstaclesToRemove.add(i);
            }
        }
        for(int j = 0; j < obstaclesToRemove.size(); j++){
            me.obstacles.remove(obstaclesToRemove.get(j));
        }
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
        if (numNorth == lowest) {
            leastVisited.add(direction.NORTH);
        }
        if(numEast == lowest) {
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

    public direction getLeastVisitedFrom(direction firstDirection, direction secondDirection){
        int lowest = 200;

        int numFirst = (okayToGo(firstDirection))?(getNumTimesVisited(me.one_safe(firstDirection))):(200);
        int numSecond = (okayToGo(secondDirection))?(getNumTimesVisited(me.one_safe(secondDirection))):(200);

        if(numFirst < lowest){
            lowest = numFirst;
        }
        if(numSecond < lowest){
            lowest = numSecond;
        }
        if(numFirst == lowest){
            return firstDirection;
        }else{
            return secondDirection;
        }
    }

    public direction getLeastVisitedFrom(direction firstDirection, direction secondDirection, direction thirdDirection){
        int lowest = 200;

        int numFirst = (okayToGo(firstDirection))?(getNumTimesVisited(me.one_safe(firstDirection))):(200);
        int numSecond = (okayToGo(secondDirection))?(getNumTimesVisited(me.one_safe(secondDirection))):(200);
        int numThird = (okayToGo(thirdDirection))?(getNumTimesVisited(me.one_safe(thirdDirection))):(200);

        if(numFirst < lowest){
            lowest = numFirst;
        }
        if(numSecond < lowest){
            lowest = numSecond;
        }
        if(numThird < lowest){
            lowest = numThird;
        }
        if(numFirst == lowest){
            return firstDirection;
        }
        else if(numSecond == lowest){
            return secondDirection;
        }
        else{
            return thirdDirection;
        }
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

    public direction pickRandomlyBetween(direction firstDir, direction secondDir, direction thirdDir, direction fourthDir) {
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

    public int pickRandomlyBetweenAndMove(direction firstDir, direction secondDir, direction thirdDir, direction fourthDir) {
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

    public direction pickRandomlyBetween(ArrayList<direction> directions){
        direction dir = direction.DONOTHING;

        int num = randomInt(1, directions.size());
        for(int i = 0; i < directions.size(); i++){
            if(num == i){
                dir = directions.get(i);
                break;
            }
        }
        return dir;
    }

    public int pickRandomlyBetweenAndMove(ArrayList<direction> directions){
        return move(pickRandomlyBetween(directions));
    }

    public int moveToOneOfLeastVisitedSquares(){
        int whatToDo = pickRandomlyBetweenAndMove(getLeastVisitedSurroundingSquares());
        return whatToDo;
    }

    public direction pickOneOfLeastVisitedSquares(){
        return pickRandomlyBetween(getLeastVisitedSurroundingSquares());
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

    public boolean okayToGo(ArrayList<direction> directions){
        boolean okayToGoAllDirections = true;
        for(int i = 0; i < directions.size(); i++){
            if(!okayToGo(directions.get(i))){
                okayToGoAllDirections = false;
                break;
            }
        }
        return okayToGoAllDirections;
    }

    public boolean okayToGo(direction dir){
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

    public boolean isObst(direction dir){
        switch(dir){
            case NORTH:
                return obstNorth;
            case EAST:
                return obstEast;
            case SOUTH:
                return obstSouth;
            case WEST:
                return obstWest;
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
            obstNorth = (inEnvironment.isObstacleNorthImmediate() || (map[me.position.y - 1][me.position.x] == 'X'));
        }

        if(me.position.y == mapHeight - 1){
            obstSouth = inEnvironment.isObstacleSouthImmediate();
        }else{
            obstSouth = (inEnvironment.isObstacleSouthImmediate() || (map[me.position.y + 1][me.position.x] == 'X'));
        }

        if(me.position.x == mapHeight -1){
            obstEast  = inEnvironment.isObstacleEastImmediate();
        }else{
            obstEast  = (inEnvironment.isObstacleEastImmediate() || (map[me.position.y][me.position.x + 1] == 'X'));
        }

        if(me.position.x == 0){
            obstWest  = inEnvironment.isObstacleWestImmediate();
        }else{
            obstWest  = (inEnvironment.isObstacleWestImmediate() || (map[me.position.y][me.position.x - 1] == 'X'));
        }

        obstNorthEastSouth = (obstNorth && obstEast && obstSouth);
        obstEastSouthWest = (obstEast && obstSouth && obstWest);
        obstSouthWestNorth = (obstSouth && obstWest && obstNorth);
        obstWestNorthEast = (obstWest && obstNorth && obstEast);
        obstEveryDirection = (obstWest && obstNorth && obstEast && obstSouth);

        if (obstNorth && me.position.y != 0) {
            map[me.position.y - 1][me.position.x] = 'X';
            addToClosedList(me.position.oneNorth());
        }
        if (obstEast && me.position.x != mapHeight - 1) {
            map[me.position.y][me.position.x + 1] = 'X';
            addToClosedList(me.position.oneEast());
        }
        if (obstSouth && me.position.y != mapHeight - 1) {
            map[me.position.y + 1][me.position.x] = 'X';
            addToClosedList(me.position.oneSouth());
        }
        if (obstWest && me.position.x != 0) {
            map[me.position.y][me.position.x - 1] = 'X';
            addToClosedList(me.position.oneWest());
        }
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
        } else if(positionIsEast(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.EAST;
        }else if(positionIsSouth(defenseWallCenter.position)){
            defenseWallCenter.dir = direction.SOUTH;
        }else{
            defenseWallCenter.dir = direction.WEST;
        }
    }

    public void setMapSquare(Coordinate pos, char c) {
        //map[pos.x][pos.y] = c;
        map[pos.y][pos.x] = c;
    }

    public void moveMeOnMap(Coordinate source, Coordinate destination) {
        if(obstInThreeDirections()){
            setMapSquare(source, 'X');
            addToClosedList(source);
        }else {
            setMapSquare(source, ' ');
            addToOpenList(destination);
        }
        setMapSquare(destination, me.name);
    }

    public void updateTimesVisited(Coordinate pos){
        timesVisited[pos.y][pos.x]++;
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

    public void makeEmptyAstarMap() {
        astarmap = new char[mapHeight][mapHeight];
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapHeight; j++) {
                if(isInList(astar.open, new Coordinate(j, i))){
                    astarmap[i][j] = ' ';
                }else{
                    astarmap[i][j] = '.';
                }
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

        map[ourBase.position.y][ourBase.position.x] = 'O';
        map[enemyBase.position.y][enemyBase.position.x] = 'E';

        for (int i = 0; i < agents.size(); i++) {
            map[agents.get(i).position.y][agents.get(i).position.x] = agents.get(i).name;
        }

        System.out.println("----------");
        for (int row = 0; row < mapHeight; row++) {
            for (int column = 0; column < mapHeight; column++) {
                System.out.print(map[row][column]);
            }
            System.out.println();
        }
        System.out.println("----------");
    }

    public void printAStarMap() {

        astarmap[ourBase.position.y][ourBase.position.x] = 'O';
        astarmap[enemyBase.position.y][enemyBase.position.x] = 'E';

        System.out.println("----------");
        for (int row = 0; row < mapHeight; row++) {
            for (int column = 0; column < mapHeight; column++) {
                System.out.print(astarmap[row][column]);
            }
            System.out.println();
        }
        System.out.println("----------");
    }

    public void printMapAndTimesVisited() {

        map[ourBase.position.y][ourBase.position.x] = 'O';
        map[enemyBase.position.y][enemyBase.position.x] = 'E';

        for (int i = 0; i < agents.size(); i++) {
            map[agents.get(i).position.y][agents.get(i).position.x] = agents.get(i).name;
        }

        System.out.println("----------   ----------");
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapHeight; j++) {
                System.out.print(map[i][j]);
            }
            System.out.print("   ");
            for (int j = 0; j < mapHeight; j++) {
                System.out.print(timesVisited[i][j]);
            }
            System.out.println();
        }
        System.out.println("----------   ----------");
    }

    public void printMapAndTimesVisitedWithShortestPath(ArrayList<Coordinate> path) {

        map[ourBase.position.y][ourBase.position.x] = 'O';
        map[enemyBase.position.y][enemyBase.position.x] = 'E';

        for (int row = 0; row < agents.size(); row++) {
            map[agents.get(row).position.y][agents.get(row).position.x] = agents.get(row).name;
        }

        Coordinate pos = new Coordinate();

        System.out.println("----------   ----------");
        for (int row = 0; row < mapHeight; row++) {
            for (int column= 0; column < mapHeight; column++) {
                pos.set(column, row);
                if(isInList(path, pos) && !isSamePositionAsAnyAgent(pos)){
                    System.out.print('@');
                }else{
                    System.out.print(map[row][column]);
                }
            }
            System.out.print("   ");
            for (int column= 0; column < mapHeight; column++) {
                System.out.print(timesVisited[row][column]);
            }
            System.out.println();
        }
        System.out.println("----------   ----------");
        printCoordinateList(path);
    }

    public void printCoordinateList(ArrayList<Coordinate> list){
        for(int i = 0; i < list.size(); i++){
            System.out.print(list.get(i).toString() + " ");
        }
        System.out.println();
    }

    public boolean isInList(ArrayList<Coordinate> list, Coordinate coordinate){
        for(int i = 0; i < list.size(); i++){
            if(coordinate.isEqualTo(list.get(i))){
                return true;
            }
        }
        return false;
    }

    //returns -1 if point is not in the list
    public int getIndexOfPointInList(ArrayList<Coordinate> list, Coordinate point){
        for(int i = 0; i < list.size(); i++){
            if(point.isEqualTo(list.get(i))){
                return i;
            }
        }
        return -1;
    }

    public boolean isSamePositionAsAnyAgent(Coordinate position){
        for (int i = 0; i < agents.size(); i++) {
            if(position.isEqualTo(agents.get(i).position)){
                return true;
            }
        }
        return false;
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

    public direction getDirectionOfPointRelativeToMe(Coordinate point){
        if(positionIsNorth(point) && positionIsEast(point)){
            return direction.NORTHEAST;
        }else if(positionIsEast(point) && positionIsSouth(point)){
            return direction.SOUTHEAST;
        }else if(positionIsSouth(point) && positionIsWest(point)){
            return direction.SOUTHWEST;
        }else if(positionIsNorth(point) && positionIsWest(point)){
            return direction.NORTHWEST;
        }else if(positionIsNorth(point)){
            return direction.NORTH;
        }else if(positionIsEast(point)){
            return direction.EAST;
        }else if (positionIsSouth(point)){
            return direction.SOUTH;
        }else{
            return direction.WEST;
        }
    }

    public int manhattanDistance(Coordinate point1, Coordinate point2){
        int distanceHorizontal = Math.abs(point1.x - point2.x);
        int distanceVertical = Math.abs(point1.y - point2.y);

        return (distanceHorizontal + distanceVertical) - 1;
    }

    public Coordinate closestToPositionFromList(Coordinate position, ArrayList<Coordinate> list){
        int lowestManhattanDistance = 999999999;
        int currentManhattanDistance = 99999999;
        for(int i = 0; i < list.size(); i++){
            currentManhattanDistance = manhattanDistance(list.get(i), position);
            if(currentManhattanDistance < lowestManhattanDistance){
                lowestManhattanDistance = currentManhattanDistance;
            }
        }

        Coordinate closestPoint = new Coordinate();
        for(int i = 0; i < list.size(); i++){
            currentManhattanDistance = manhattanDistance(list.get(i), position);
            if(currentManhattanDistance == lowestManhattanDistance){
                closestPoint = list.get(i);
            }
        }
        return closestPoint;
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

    public boolean positionIsNorthWest(Coordinate pos) {
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

    public obstacle getObstacleDirectionFromDirection(direction dir){
        obstacle obst = obstacle.NONE;

        switch(dir){
            case NORTH:
                obst = obstacle.NORTH_WALL;
                break;
            case EAST:
                obst = obstacle.EAST_WALL;
                break;
            case SOUTH:
                obst = obstacle.SOUTH_WALL;
                break;
            case WEST:
                obst = obstacle.WEST_WALL;
                break;
        }
        return obst;
    }

    public direction getDirectionFromObstacleDirection(obstacle obst){
        direction dir = direction.DONOTHING;

        switch(obst){
            case NORTH_WALL:
                dir = direction.NORTH;
                break;
            case EAST_WALL:
                dir = direction.EAST;
                break;
            case SOUTH_WALL:
                dir = direction.SOUTH;
                break;
            case WEST_WALL:
                dir = direction.WEST;
                break;
        }
        return dir;
    }

    public ArrayList<direction> getDirectionsFromObstacles(ArrayList<obstacle> obstacles){
        ArrayList<direction> directions = new ArrayList<direction>();
        for(int i = 0; i < obstacles.size(); i++){
            directions.add(getDirectionFromObstacleDirection(obstacles.get(i)));
        }
        return directions;
    }
}
