#Generates N terms of a random sequence converging to a.
rand_seq <- function(a, N, rate = 1)
{
  X <- rep(0, N) #Creates a of N zeroes
  for (i in 1:N)
  {
    #Sets X[i] to be a random number a distance at most 1/(i*rate) of a
    X[i] <- runif(1, min = a - (1/(i*rate)), max = a + (1/(i*rate)))
  }
  return(X)
}

#Generates N terms of a random(ish) increasing sequence converging to a.
rand_inc_seq <- function(a, N, rate = 1)
{
  X <- rep(0, N)
  for (i in 1:N)
  {
    #Sets X[i] to be a random number in the interval [a - (1/(i*rate)), a - (1/((i+1)*rate))]
    X[i] <- runif(1, min = a - (1/(i*rate)), max = a - (1/((i+1)*rate)))
  }
  return(X)
}

M <- 100 #How many terms we want in the sequence

a <- 4*pi #A nice real number

rate <- .1 #So the sequence doesn't converge too quickly

sqnce <- rand_seq(a,M,rate) #Try changing to rand_inc_seq

#Run this loop to generate M plots of the sequence with more and more terms.
#Saves them as (many) png in the working directory.
#Use, for example, https://ezgif.com/maker to make these into a gif.
for (i in 1:M)
{
  #Saves as i.png for different values of i
  png(paste(as.character(i),".png",sep="")) 
  #Creates a copy of sqnce which we will modify
  X <- sqnce
  #This has the effect of only keeping the first i terms of sqnce
  length(X) <- i
  #Creates the vector (0,1/i, 2/i,..., i/i=1)
  partition <- (1/i)*(0:i)

  #Change ylim if it the plot doesn't fit your sequence (may happen if you mess around with the parameters)
  plot(partition, c(NA,X),pch = 20, xlim = c(0,1), ylim=c(min(c(a - (1/rate), 0)),a + (1/(rate))),axes = FALSE,xlab="",ylab = "",main=paste("n =",as.character(i)))
  
  #These just add the "rectangles"
  #It's "h" for histogram (vertical lines) and "S" for stairs
  lines(partition, c(NA,X), type = "h")
  lines(partition, c(NA,X), type = "S")
  
  #For some reason the rectangles do not work for the first term
  #So we add it manually
  y <- rep(NA, length(partition))
  y[1] <- X[1]
  y[2]<- X[1]
  lines(partition, y,type="l") # "l" means line

  #x axis (h means horizontal)
  abline(h=0)
  #y axis (v means vertical)
  abline(v=0)
  #Line indicating the value of a
  abline(h = a, lty = 4, col= "red")
  #Add labels
  text(0,a,expression(italic("a")),pos = 2,offset= 0.1)
  text(1,0,"1",pos = 1,offset= 0.1)
  
  #Important command when saving images to the directory
  #Do not touch
  dev.off()
}
