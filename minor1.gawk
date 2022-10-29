BEGIN{ FS="," 
    print("Studen Average Test Scores")
    print("NAME""\t\t\t""AVERAGE")
    start=0;
    cnt=0;
    score=0;
}

{
    if(start==0)
        start=1;
    else if(start==1)
        start=2;
    if($3=="A")
    {
        Name=$2" "$1;
        Average=($4+$5+$6)/3;
        printf("%-25s %5.1f\n", Name,Average) 
        cnt++;
        score+=Average;
    }
}
END{
    printf("%d Students with average score of %.1f\n", cnt, (score/cnt));
}
