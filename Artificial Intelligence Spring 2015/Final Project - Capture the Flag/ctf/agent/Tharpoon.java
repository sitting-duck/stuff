package ctf.agent;

import java.lang.Integer;
import java.lang.System;
import java.util.ArrayList;
import java.lang.Math;
import ctf.common.AgentAction;
import ctf.common.AgentEnvironment;
import ctf.agent.Agent;
import ctf.common.AgentAction;

public class Tharpoon extends Agent{

    private class Agent{
        public Integer number;
        public char name;
        public objective currentObjective;
        public Coordinate<Integer> spawn;
        public Coordinate<Integer> position;
        public ArrayList<Coordinate<Integer>> squaresTravelled;
        public boolean hasFlag;
        public boolean foundBase;

        public Agent(){
            number = -1;
            currentObjective = objective.INITIALIZE;
            spawn = new Coordinate<Integer>();
            position = new Coordinate<Integer>();
            squaresTravelled = new ArrayList<Coordinate<Integer>>();
            hasFlag = false;
            foundBase = false;
        }
    }

    private class Place{
        String name;
        direction dir;
        Coordinate<Integer> position;

        Place(String name){
            this.name = name;
            position = new Coordinate<Integer>();
        }
    }

    private class Coordinate<N> {
        public N x;
        public N y;
        public Coordinate(){}
        public Coordinate(N x, N y){this.x = x; this.y = y;}
        public void set(N x, N y) {this.x = x; this.y = y; }
        public void set(Coordinate<N> otherCoordinate){this.x = otherCoordinate.x; this.y = otherCoordinate.y;}
        public String toString(){return "(" + x + ", " + y + ")";}
    }

    //Agents
    private final static int MAX_NUM_AGENTS = 2;
    private static ArrayList<Agent> agents = new ArrayList<Agent>();
    private Agent me;
    private Agent otherAgent;
    private enum objective {INITIALIZE, SEEK_ENEMY_BASE, SEEK_OUR_BASE, RETRIEVE_FRIENDLY_FLAG }


    //Map
    private static char[][] map;
    private int mapHeight = 10;         //it is known that mapHeight == mapLength
    Place ourBase;
    Place enemyBase;
    ArrayList<Place> pointsOfInterest = new ArrayList<Place>();
    private enum direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST}


    //Environment Variables
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

    public Tharpoon(){

        //Agent
        if(agents.size() == MAX_NUM_AGENTS){agents.clear();}
        me = new Agent();
        agents.add(me);
        me.number = agents.size() - 1;
        me.name = (char)('a' + me.number);
        System.out.println("added agent " + me.name + me.number);

        //Map
        makeEmptyMap();
        ourBase = new Place("ourBase");
        enemyBase = new Place("enemyBase");
        pointsOfInterest.add(ourBase);
        pointsOfInterest.add(enemyBase);
    }

    public int getMove( AgentEnvironment inEnvironment ) {

        //init
        queryEnvironment(inEnvironment);
        if(me.currentObjective == objective.INITIALIZE){
            determineMySpawnAndInitialPosition();
            if(me.number == agents.size() - 1){determineBasePositions();}

            me.currentObjective = objective.SEEK_ENEMY_BASE;
        }

        //print only after every complete move (ie, both agents have moved)
        if(me.number == 1){printMap();}

        return AgentAction.DO_NOTHING;

    }

    public void determineMySpawnAndInitialPosition(){

        if(enemyBaseEast && ourBaseSouth){
            me.spawn.set(0, 0);
        }else if(enemyBaseEast && ourBaseNorth){
            me.spawn.set(0, mapHeight - 1);
        }else if(enemyBaseWest && ourBaseNorth){
            me.spawn.set(mapHeight -1, mapHeight - 1);
        }else if(enemyBaseWest && ourBaseSouth){
            me.spawn.set(mapHeight - 1, 0);
        }
        me.position.set(me.spawn);
        System.out.println("agent " + me.number + " init: " + me.position.toString());
    }

    public void determineBasePositions(){
        if(enemyBaseWest){
            ourBase.position.set(9, 5);
            enemyBase.position.set(0, 5);
        }else if(enemyBaseEast){
            ourBase.position.set(0, 5);
            enemyBase.position.set(9, 5);
        }
        System.out.println("enemy base: " + enemyBase.position.toString());
        System.out.println("ourBase: " + ourBase.position.toString());
    }

    public void setMapSquare(Coordinate<Integer> pos, char c){
        map[pos.x][pos.y] = c;
    }

    public void queryEnvironment(AgentEnvironment inEnvironment){

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

    public char[][] makeEmptyMap(){
        map = new char[mapHeight][mapHeight];
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapHeight; j++) {
                map[i][j] = '.';
            }
        }
        return map;
    }

    public void printMap (){

        map[ourBase.position.x][ourBase.position.y] = 'O';
        map[enemyBase.position.x][enemyBase.position.y] = 'E';

        for(int i = 0; i < agents.size(); i++){
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

}