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
        public int agentNum;
        public objective currentObjective;
        public Coordinate<Integer> position;
        public Coordinate<Integer> spawn;
        public ArrayList<Coordinate<Integer>> squaresTravelled;
        public boolean hasFlag;
        public boolean foundBase;

        public Agent(){
            agentNum = -1;
            currentObjective = objective.INITIALIZE;
            position = new Coordinate<Integer>();
            spawn = new Coordinate<Integer>();
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
    }

}