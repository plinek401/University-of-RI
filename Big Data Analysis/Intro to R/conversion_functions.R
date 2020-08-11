CtoF <- function(tempC){
  if(!is.numeric(tempC)){
    stop("Integer parameter expected.")
  }
  tempF <- (tempC) * 9/5 + 32 
  return(tempF)
}

FtoC <- function(tempF){
  if(!is.numeric(tempF)){
    stop("Integer parameter expected.")
  }
  tempC <- (tempF-32) * 5/9 
  return(tempC)
}

mm_to_inches <- function(mm){
  if(!is.numeric(mm)){
    stop("Integer parameter expected.")
  }
  inches = mm/25.4
  return(inches)
}
