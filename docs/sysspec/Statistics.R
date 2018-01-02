# PAWI Reference Clock and Sensor statistics
# date: 15.12.2017, 09:30, Temperature 23.74°, humidity 27.16%
par(mfrow=c(1,1))
frequencies_no_gps <- c(11980515, 11980483, 11980481, 11980487, 11980527, 11980493, 11980532, 11980539, 11980500, 11980546, 11980505, 11980511, 11980518, 11980520, 11980517, 11980521, 11980559, 11980555, 11980529, 11980521)

frequencies_gps    <- c(11980579, 11980569, 11980569, 11980577, 11980577, 11980575, 11980578, 11980581, 11980582, 11980577, 11980578, 11980570, 11980585, 11980585, 11980582, 11980581, 11980584, 11980589, 11980590, 11980589)
boxplot(frequencies_no_gps, frequencies_gps, xaxt="n", ylab="Referenz-Frequenzen")
axis(1, at = c(1,2), labels = c("no GPS", "GPS"))

#Min-Max Differenz
max(frequencies_no_gps) - min(frequencies_no_gps)
max(frequencies_gps) - min(frequencies_gps)

# Mehrere Grafiken neben- und untereinander 
par(mfrow=c(1,2))
hist(frequencies_no_gps, xlab = "Ermittelte Frequenzen\nMin-Max-Differenz: 78", ylab="Häufigkeit", main = "Histogramm ohne GPS", freq = FALSE)
box()
x <- frequencies_no_gps
curve(dnorm(x, mean=mean(frequencies_no_gps), sd=sd(frequencies_no_gps)), add=T)
hist(frequencies_gps, xlab = "Ermittelte Frequenzen\nMin-Max-Differenz: 21", ylab="Häufigkeit", main = "Histogramm mit GPS", freq = FALSE)
box()
x <- frequencies_gps
curve(dnorm(x, mean=mean(frequencies_gps), sd=sd(frequencies_gps)), add=T)

## Theoretische Quantile 
alphak <- (seq(1,length(frequencies_no_gps),by=1)-0.5)/length(frequencies_no_gps) 
quantile.theor <- qnorm(alphak,mean=mean(frequencies_no_gps),sd=sd(frequencies_no_gps))

## 	Empirische Quantile
quantile.empir <- sort(frequencies_no_gps)
qqnorm(frequencies_no_gps, xlab="Theoretische Quantile", ylab="Empirische Quantile", main = "Verteilung ohne GPS")
qqline(frequencies_no_gps)

quantile.empir <- sort(frequencies_gps)
qqnorm(frequencies_gps, xlab="Theoretische Quantile", ylab="Empirische Quantile", main = "Verteilung mit GPS")
qqline(frequencies_gps)

12000000 * 20 - sum(frequencies_no_gps)
12000000 * 20 - sum(frequencies_gps)

