package ctf.agent;


import ctf.common.AgentEnvironment;
import ctf.agent.Agent;

import java.lang.Integer;
import java.lang.System;
import java.util.ArrayList;

import ctf.common.AgentAction;



public class TharpoonMap{



    public class Pair<L, R> {
        private L l;
        private R r;
        public Pair(L l, R r){
            this.l = l;
            this.r = r;
        }
        public L getLeft(){ return l; }
        public R getRight(){ return r; }
        public void setLeft(L l){ this.l = l; }
        public void setRight(R r){ this.r = r; }
        public void setPair(L l, R r) {setLeft(l); setRight(r); }
    }

    public Integer mapDimension;

    public ArrayList<Pair<Integer, Integer>> obstacles;

    public Pair<Integer, Integer> enemyBase;

    public Pair<Integer, Integer> ourBase;


    public TharpoonMap(Integer _mapDimension){
        mapDimension = _mapDimension;
    }

}

