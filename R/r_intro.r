# Found here: https://cran.r-project.org/doc/manuals/r-release/R-intro.pdf

x <- rnorm(50)
y <- rnorm(x)
plot(x, y)
ls() 
rm(x, y) 
x <- 1:20

w <- 1 + sqrt(x)/2
dummy <- data.frame(x=x, y= x + rnorm(x)*w)
fm <- lm(y ~ x, data=dummy)
summary(fm)
fm1 <- lm(y ~ x, data=dummy, weight=1/w^2)
summary(fm1)
attach(dummy)
lrf <- lowess(x, y)
plot(x, y)
lines(x, lrf$y)
abline(0, 1, lty=3)
abline(coef(fm))

abline(coef(fm1), col = "red")
detach()
plot(fitted(fm), resid(fm), xlab="Fitted values", ylab="Residuals", main="Residuals vs Fitted")
qqnorm(resid(fm), main="Residuals Rankit Plot")
rm(fm, fm1, lrf, x, dummy)

filepath <- system.file("data", "morley.tab" , package="datasets")
file.show(filepath)
mm <- read.table(filepath)
mm 


mm$Expt <- factor(mm$Expt)
mm$Run <- factor(mm$Run)
attach(mm)
plot(Expt, Speed, main="Speed of Light Data", xlab="Experiment No.")


