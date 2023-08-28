#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LECTURE_NAME 50
#define NUM_LECTURES 20
#define NUM_SCORES 10

static char* scores[NUM_SCORES] = { "A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F", "P" };
enum { APP, A00, BPP, B00, CPP, C00, DPP, D00, FFF, PPP };

typedef struct
{
	char name[MAX_LECTURE_NAME];
	int grade;
	int score;
} lecture;

int get_scores(char* score)
{
	for (int i = 0; i < NUM_SCORES; i++)
	{
		if (strcmp(scores[i], score) == 0)
		{
			return i;
		}
	}
	return 0;
}

double scoreing(int score)
{
	double ret;

	switch (score)
	{
	case APP:
		ret = 4.5;
		break;
	case A00:
		ret = 4.0;
		break;
	case BPP:
		ret = 3.5;
		break;
	case B00:
		ret = 3.0;
		break;
	case CPP:
		ret = 2.5;
		break;
	case C00:
		ret = 2.0;
		break;
	case DPP:
		ret = 1.5;
		break;
	case D00:
		ret = 1.0;
		break;
	case FFF:
		ret = 0.0;
		break;
	case PPP:
		ret = 0.0;
		break;
	}
	return ret;
}

int main(void)
{
	lecture* lectures;
	int num_total;
	double total;
	int total_grade;

	lectures = (lecture*)calloc(NUM_LECTURES, sizeof(lecture));
	num_total = 0;
	total = 0;
	total_grade = 0;

	for (int i = 0; i < NUM_LECTURES; i++)
	{
		double grade;
		char score[5];
		double sum;

		scanf("%s %lf %s", lectures[i].name, &grade, score);

		lectures[i].grade = grade;
		lectures[i].score = get_scores(score);

		if (lectures[i].score == PPP)
		{

		}
		else
		{
			sum = grade * scoreing(lectures[i].score);
			total_grade = total_grade + grade;
			total = total + sum;
			num_total = num_total + 1;
		}
	}
	printf("%lf", total / total_grade);
}