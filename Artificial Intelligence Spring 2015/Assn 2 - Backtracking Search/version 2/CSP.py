__author__ = 'ashley'


class CSP:
    """CSP ie Constraint Satisfaction Problem contains a set of Variables to be solved"""

    def __init__(self, variablesArg, constraintsArg, consistencyEnforcingProcedureArg):
        self.variables = variablesArg
        self.constraints = constraintsArg
        self.consistencyEnforcingProcedure = consistencyEnforcingProcedureArg

        # calculate the degree for each var
        for con in self.constraints:
            for var in self.variables:
                if con.var1 == var.name:
                    var.degree += 1
                if con.var2 == var.name:
                    var.degree += 1

    # checks the assignment passed to it against the constraints of this CSP
    def isCompleteAndValid(self, assignmentArg):

        # check that every variable has an assignment
        if len(assignmentArg) != len(self.variables):
            return False

        # check that all constraints are valid
        for constraint in self.constraints:
            if self.checkConstraint(assignmentArg, constraint) == False:
                return False

        # if we've looped through every constraint check and empty variable check and not a single one returned false,
        # then we can return true
        return True

    # checks a single constraint against the assignment, returns true or false
    def checkConstraint(self, assignmentArg, constraintArg):
        value1 = self.variables[constraintArg.var1]
        if(constraintArg.ops[constraintArg.oper](constraintArg.var1, constraintArg.var2)):
            return True
        else:
            return False