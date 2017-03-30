//---------------------------------------------------------------------------
// labels.c
//
// Storage and lookup of graph vertex and edge labels.
//
// Subdue 5
//---------------------------------------------------------------------------

#include "subdue.h"


// Declare global variables.
VectorLimitEntry * vectorLimits;
int vectorLimitsEntryCount;
//---------------------------------------------------------------------------
// NAME:    AllocateLabelList
//
// INPUTS:  (void)
//
// RETURN:  (LabelList *)
//
// PURPOSE: Allocate memory for empty label list.
//---------------------------------------------------------------------------

LabelList *AllocateLabelList(void)
{
   LabelList *labelList;
   labelList = (LabelList *) malloc(sizeof(LabelList));
   if (labelList == NULL)
      OutOfMemoryError("AllocateLabelList:labelList");
   labelList->size = 0;
   labelList->numLabels = 0;
   labelList->labels = NULL;
   return labelList;
}


//---------------------------------------------------------------------------
// NAME:    StoreLabel
//
// INPUTS:  (Label *label) - label to be stored (if necessary)
//          (LabelList *labelList) - list to contain label
//
// RETURN:  (ULONG) - label's index in given label list
//
// PURPOSE: Stores the given label, if not already present, in the
// given label list and returns the label's index.  The given label's
// memory can be freed after executing StoreLabel.
//---------------------------------------------------------------------------

ULONG StoreLabel(Label *label, LabelList *labelList)
{
   ULONG labelIndex;
   Label *newLabelList;
   char *stringLabel;

   labelIndex = GetLabelIndex(label, labelList);
   if (labelIndex == labelList->numLabels) 
   { // i.e., label not found
      // make sure there is room for a new label
      if (labelList->size == labelList->numLabels) 
      {
         labelList->size += LIST_SIZE_INC;
         newLabelList = (Label *) realloc(labelList->labels,
                                          (sizeof(Label) * labelList->size));
         if (newLabelList == NULL)
            OutOfMemoryError("StoreLabel:newLabelList");
         labelList->labels = newLabelList;
      }
      // store label
      labelList->labels[labelList->numLabels].labelType = label->labelType;
      switch(label->labelType) 
      {
         case STRING_LABEL:
            stringLabel = (char *) malloc
                          (sizeof(char) * 
                           (strlen(label->labelValue.stringLabel)) + 1);
            if (stringLabel == NULL)
               OutOfMemoryError("StoreLabel:stringLabel");
            strcpy(stringLabel, label->labelValue.stringLabel);
            labelList->labels[labelList->numLabels].labelValue.stringLabel =
               stringLabel;
            break;
         case NUMERIC_LABEL:
            labelList->labels[labelList->numLabels].labelValue.numericLabel =
               label->labelValue.numericLabel;
            break;
         case VECTOR_LABEL:
        	labelList->labels[labelList->numLabels].labelValue.vStruct = label->labelValue.vStruct;

        	// Allocate space for string label and assign it
        	labelList->labels[labelList->numLabels].labelValue.vStruct.stringLabel =
        			(char *) malloc
                    (sizeof(char) *
                     (strlen(label->labelValue.vStruct.stringLabel)) + 1);
        	strcpy(labelList->labels[labelList->numLabels].labelValue.vStruct.stringLabel,
        			label->labelValue.vStruct.stringLabel);

        	// Vector label allocation and assignment
        	labelList->labels[labelList->numLabels].labelValue.vStruct.vectorLabel =
        			malloc(label->labelValue.vStruct.numberOfDimensions * sizeof(double));

        	int dimItr=0;
        	for (dimItr = 0; dimItr < label->labelValue.vStruct.numberOfDimensions; ++dimItr) {
        		labelList->labels[labelList->numLabels].labelValue.vStruct.vectorLabel[dimItr] =
        				label->labelValue.vStruct.vectorLabel[dimItr];
			}

        	// Record maximum distance over two samples over the data.
        	RecordMaxDistance(labelList);

            break;
         default:
            break;  // error
      }
      labelList->labels[labelList->numLabels].used = FALSE;
      labelList->numLabels++;
   }
   /*
   PrintLabel(labelIndex, labelList, stdout);
   fflush(stdout);
   */
   return labelIndex;
}

//---------------------------------------------------------------------------
// NAME:    RecordMaxDistance
//
// INPUTS:  (LabelList *labelList) - the label list to be estimated for max distance
//
// RETURN: void
//
// PURPOSE: Tests the distance with the last element of label matrix with
// the rest of labels of same vector type. If the distance found is larger
// than the last recorded value, it is replaced with the new one.
//---------------------------------------------------------------------------
void RecordMaxDistance(LabelList *labelList)
{
	// Calculate the distance between the last label and each label on the list.
	// Get their maximum.
	int labelItr;
	double curDist = 0, maxDist = 0;
	for (labelItr = 0; labelItr < labelList->numLabels; ++labelItr) {
		if (!VectorCompatible(&(labelList->labels[labelItr]), &(labelList->labels[labelList->numLabels])))
				curDist = -1;
		else curDist = GetVectorDistance(&(labelList->labels[labelItr]),
							&(labelList->labels[labelList->numLabels]), FALSE);
		if (curDist>maxDist)
			maxDist = curDist;
	}

	// Save this maximum if it is larger than recorded value. Create
	// row if it does not exist for this vector type.
	if (maxDist > 0)
	{
		if (vectorLimitsEntryCount == 0 && vectorLimits == NULL)
		{
			vectorLimits = (VectorLimitEntry*) malloc(sizeof(VectorLimitEntry));
			vectorLimits[0].name = malloc(strlen(labelList->labels[labelList->numLabels].labelValue.vStruct.stringLabel) * sizeof(char) + 1);
			strcpy(vectorLimits[0].name, labelList->labels[labelList->numLabels].labelValue.vStruct.stringLabel);
			vectorLimits[0].numberOfDimensions = (double) labelList->labels[labelList->numLabels].labelValue.vStruct.numberOfDimensions;
			vectorLimits[0].distType = (double) labelList->labels[labelList->numLabels].labelValue.vStruct.vectComparisonType;
			vectorLimits[0].maxDistance = maxDist;
			vectorLimitsEntryCount++;
		}
		else {
			// If we can locate the row, we'll update the maximum distance for this type.
			int correctRow = -1, itr;
			for (itr = 0; itr < vectorLimitsEntryCount; ++itr) {
				if ( !strcmp(vectorLimits[itr].name, labelList->labels[labelList->numLabels].labelValue.vStruct.stringLabel)&&
						vectorLimits[itr].numberOfDimensions == labelList->labels[labelList->numLabels].labelValue.vStruct.numberOfDimensions &&
						vectorLimits[itr].distType == labelList->labels[labelList->numLabels].labelValue.vStruct.vectComparisonType)
				{
					correctRow = itr;
					if (vectorLimits[itr].maxDistance < maxDist){
						vectorLimits[itr].maxDistance = maxDist;
					}
				}
			}
			// If row is not found, we should just realloc the array and write the triple to the end.
			if (correctRow == -1){
				vectorLimits = (VectorLimitEntry*) realloc((void *) vectorLimits, (vectorLimitsEntryCount + 1) * sizeof(VectorLimitEntry));
				vectorLimits[vectorLimitsEntryCount].name = malloc(strlen(labelList->labels[labelList->numLabels].labelValue.vStruct.stringLabel) * sizeof(char) + 1);
				strcpy(vectorLimits[vectorLimitsEntryCount].name, labelList->labels[labelList->numLabels].labelValue.vStruct.stringLabel);
				vectorLimits[vectorLimitsEntryCount].numberOfDimensions = labelList->labels[labelList->numLabels].labelValue.vStruct.numberOfDimensions;
				vectorLimits[vectorLimitsEntryCount].distType = labelList->labels[labelList->numLabels].labelValue.vStruct.vectComparisonType;
				vectorLimits[vectorLimitsEntryCount].maxDistance = maxDist;
				vectorLimitsEntryCount++;
			}
		}
	}
}

//---------------------------------------------------------------------------
// NAME:    GetLabelIndex
//
// INPUTS:  (Label *label) - label being sought
//          (LabelList *labelList) - list in which to look for label
//
// RETURN: (ULONG) - index of label in label list, or number of labels if
//                   label not found
//
// PURPOSE: Returns the index of the given label in the given label
// list.  If not found, then the index just past the end (i.e., number
// of stored labels) is returned.
//---------------------------------------------------------------------------

ULONG GetLabelIndex(Label *label, LabelList *labelList)
{
   ULONG i = 0;
   ULONG labelIndex = labelList->numLabels;
   BOOLEAN found = FALSE;

   while ((i < labelList->numLabels) && (! found)) 
   {
      if (labelList->labels[i].labelType == label->labelType) 
      {
         switch(label->labelType) 
         {
            case STRING_LABEL:
               if (strcmp(labelList->labels[i].labelValue.stringLabel,
                   label->labelValue.stringLabel) == 0) 
               {
                  labelIndex = i;
                  found = TRUE;
               }
               break;
            case NUMERIC_LABEL:
               if (labelList->labels[i].labelValue.numericLabel ==
                   label->labelValue.numericLabel) 
               {
                  labelIndex = i;
                  found = TRUE;
               }
               break;
            case VECTOR_LABEL:
            	if (VectorCompatible(label, &(labelList->labels[i])) && (VectorEqual(label, &(labelList->labels[i]))))
            	{
            		labelIndex = i;
            		found = TRUE;
            	}
            	break;
            default:
               break;  // error
         }
      }
      i++;
   }
   return labelIndex;
}

//---------------------------------------------------------------------------
// NAME:    VectorCompatible
//
// INPUTS:  (Label *label1) - first vector label to be compared
//          (Label *label2) - second vector label to be compared
//
// RETURN: (Boolean) - Return true if both vectors are of the same type,
// so they can be compared further
//
// PURPOSE: Returns 1 if and only if both labels are of the same type.
// Otherwise return 0.
//---------------------------------------------------------------------------

BOOLEAN VectorCompatible(Label *label1, Label *label2)
{
	if (label1->labelValue.vStruct.numberOfDimensions ==	// Compare number of dimensions first
			label2->labelValue.vStruct.numberOfDimensions &&
			label1->labelValue.vStruct.vectComparisonType ==	// Then, vector comparison types
					label2->labelValue.vStruct.vectComparisonType &&
					strcmp(label1->labelValue.vStruct.stringLabel,	// Their string labels finally
							label2->labelValue.vStruct.stringLabel) == 0)
	{
		return TRUE;
	}
	else return FALSE;
}

//---------------------------------------------------------------------------
// NAME:    vectorEqual
//
// INPUTS:  (Label *label1) - first vector label to be compared
//          (Label *label2) - second vector label to be compared
//
// RETURN: (Boolean) - Return true if both vector labels are strictly same.
//
// PURPOSE: Returns 1 if and only if both labels are exactly same, and
// both are vector labels of same type. Used as a helper to getLabelIndex()
// function. Otherwise return 0.
//---------------------------------------------------------------------------

BOOLEAN VectorEqual(Label *label1, Label *label2)
{
	if (fabs(label1->labelValue.vStruct.mean -		// Compare mean and stdev for
			label2->labelValue.vStruct.mean) < DOUBLE_EQUALITY_EPSILON && // fast inequality decision
			fabs(label1->labelValue.vStruct.stdev -
				label2->labelValue.vStruct.stdev) < DOUBLE_EQUALITY_EPSILON)
	{
		// In the unlikely event of getting here for two different vector labels,
		// we should compare each element one-by-one, and report inequality in the
		// case of inequal elements.
		int itr;
		for (itr = 0; itr < label1->labelValue.vStruct.numberOfDimensions; ++itr) {
			if (fabs(label1->labelValue.vStruct.vectorLabel[itr] - label2->labelValue.vStruct.vectorLabel[itr]) > DOUBLE_EQUALITY_EPSILON)
				return FALSE;
		}
	}
	else return FALSE;

	// All good, return 1.
	return TRUE;
}

//---------------------------------------------------------------------------
// NAME: SubLabelNumber
//
// INPUTS: (ULONG index) - index of label in labelList
//         (LabelList *labelList) - list of labels
//
// RETURN: (ULONG) - number from substructure label, or zero if 
//                   label is not a valid substructure label
//
// PURPOSE: Checks if label is a valid substructure label of the form
// <SUB_LABEL_STRING>_<#>, where <#> is greater than zero.  If valid,
// then <#> is returned; otherwise, returns zero.
//---------------------------------------------------------------------------

ULONG SubLabelNumber(ULONG index, LabelList *labelList)
{
   char *stringLabel;
   char prefix[TOKEN_LEN];
   char rest[TOKEN_LEN];
   BOOLEAN match;
   int i = 0;
   int labelLength;
   int prefixLength;
   ULONG subNumber;

   match = TRUE;
   subNumber = 0;
   if (labelList->labels[index].labelType == STRING_LABEL) 
   { // string label?
      stringLabel = labelList->labels[index].labelValue.stringLabel;
      labelLength = strlen(stringLabel);
      strcpy(prefix, SUB_LABEL_STRING);
      prefixLength = strlen(prefix);
      // check that first part of label matches SUB_LABEL_STRING
      if (labelLength > (prefixLength + 1))
         for (i = 0; ((i < prefixLength) && match); i++)
            if (stringLabel[i] != prefix[i])
               match = FALSE;
      if (match && (stringLabel[i] != '_')) // underscore present?
         match = FALSE;
      if (match &&                          // rest is a number?
          (sscanf((& stringLabel[i + 1]), "%lu%s", &subNumber, rest) != 1))
         subNumber = 0;
   }
   return subNumber;
}


//---------------------------------------------------------------------------
// NAME: LabelMatchFactor
//
// INPUTS: (ULONG labelIndex1)
//         (ULONG labelIndex2) - indices of labels to match
//         (LabelList *labelList) - list of labels
//
// RETURN: (double) - degree of mis-match [0.0,1.0]
//
// PURPOSE: Return the degree of mis-match between the two labels.  If
// the label indices are equal, then the degree of mis-match is 0.0,
// else 1.0.  Values between 0.0 and 1.0 may be implemented based on
// specifics of labels (e.g., threshold or tolerance matching for
// numeric labels, or semantic distance for string labels).
//---------------------------------------------------------------------------

double LabelMatchFactor(ULONG labelIndex1, ULONG labelIndex2,
          LabelList *labelList)
{
	Label label1 = labelList->labels[labelIndex1];
	Label label2 = labelList->labels[labelIndex2];
	double matchCost = 0;

	if (label1.labelType != label2.labelType)
		return 1.0;
	else
	{
		switch (label1.labelType)
		{
		case NUMERIC_LABEL:
			if (labelIndex1 == labelIndex2)
				return 0.0;
			break;
		case STRING_LABEL:
			if (labelIndex1 == labelIndex2)
				return 0.0;
			break;
		case VECTOR_LABEL:
			if (VectorCompatible(&label1, &label2))
			{
				// First, check if they are equal.
				if (VectorEqual(&label1, &label2))
					return 0.0;
				else
				{

					// Intelligent matching scheme comes into action here.
					// We implement inexact matching of labels.
					matchCost = GetVectorDistance(&label1, &label2, TRUE);
	//				printf("**LABEL MATCH FACTOR**\n");
	//				PrintLabel(labelIndex1, labelList,stdout);
	//				PrintLabel(labelIndex2, labelList,stdout);
	//				printf("\nCost:%lf\n", matchCost);
	//				printf("**LABEL MATCH FACTOR - end**\n");
	//				fflush(stdout);
					return matchCost;
				}
			}
			else
				return 1.0;
			break;
		default:	// Error
			break;
		}
	}
   return 1.0;
}

//---------------------------------------------------------------------------
// NAME:    GetVectorDistance
//
// INPUTS:  (Label *label1) - first vector label to be compared
//          (Label *label2) - second vector label to be compared
// 			(BOOLEAN normalized) - flag to apply normalization on return
//
// RETURN:  (double matchCost)
//
// PURPOSE: Calculates the distance between two vector labels using
// the specified type of distance function (through label's
// vectComparisonType property). If the labels' types / sizes / comparison
// types' differ, then maximum distance returned. If not, they are simply
// compared element by element, and the distance using the cost function
// specified is returned.
//---------------------------------------------------------------------------
double GetVectorDistance(Label *label1, Label*label2, BOOLEAN normalized){

	double matchCost = 0, normFactor = 1;
	int itr;
	int differentPositions = 0;
	double mean1 = 0, mean2 = 0;
	double dCov = 0, dVar1 = 0, dVar2 = 0;
	double dotProduct = 0, firstNorm = 0, secNorm = 0;

	switch(label1->labelValue.vStruct.vectComparisonType)
	{

	// Hamming distance
	case DIST_HAM:
		for (itr = 0; itr < label1->labelValue.vStruct.numberOfDimensions; itr++){
			if (fabs(label1->labelValue.vStruct.vectorLabel[itr] - label2->labelValue.vStruct.vectorLabel[itr]) > DOUBLE_EQUALITY_EPSILON )
				differentPositions++;
		}
		matchCost = differentPositions / (double) label1->labelValue.vStruct.numberOfDimensions;

		break;

	// Correlation distance
	case DIST_CORR:
		// Find mean values for both data sequences
		for (itr = 0; itr < label1->labelValue.vStruct.numberOfDimensions; itr++){
			mean1 += label1->labelValue.vStruct.vectorLabel[itr];
			mean2 += label2->labelValue.vStruct.vectorLabel[itr];
		}
		mean1 /= label1->labelValue.vStruct.numberOfDimensions;
		mean2 /= label1->labelValue.vStruct.numberOfDimensions;

		// Measure dissimilarity
		for (itr = 0; itr < label1->labelValue.vStruct.numberOfDimensions; itr++){
			dCov += (label1->labelValue.vStruct.vectorLabel[itr] - mean1) *
					(label2->labelValue.vStruct.vectorLabel[itr] - mean2);
			dVar1 += (label1->labelValue.vStruct.vectorLabel[itr] - mean1) *
					(label1->labelValue.vStruct.vectorLabel[itr] - mean1);
			dVar2 += (label2->labelValue.vStruct.vectorLabel[itr] - mean2) *
					(label2->labelValue.vStruct.vectorLabel[itr] - mean2);
		}

		matchCost = 1 - (dCov / sqrt(dVar1 * dVar2));

		break;

	// Cosine distance
	case DIST_COS:
		for (itr = 0; itr < label1->labelValue.vStruct.numberOfDimensions; ++itr)
		{
			dotProduct += label1->labelValue.vStruct.vectorLabel[itr] *
					label2->labelValue.vStruct.vectorLabel[itr];
			firstNorm += pow(label1->labelValue.vStruct.vectorLabel[itr], 2);
			secNorm += pow(label2->labelValue.vStruct.vectorLabel[itr], 2);
		}

		matchCost = (1 - (dotProduct / sqrt(firstNorm + secNorm))) / 2;
		break;

	// Euclidean distance
	case DIST_L2:
		for (itr = 0; itr < label1->labelValue.vStruct.numberOfDimensions; ++itr)
		{
			matchCost += pow((label1->labelValue.vStruct.vectorLabel[itr] -
								label2->labelValue.vStruct.vectorLabel[itr]), 2);
		}

		// Find the true normalization factor for this vector label type.
		if (normalized){
			for (itr = 0; itr < vectorLimitsEntryCount; ++itr) {
				if (!strcmp((char*)vectorLimits[itr].name, label1->labelValue.vStruct.stringLabel) &&
						vectorLimits[itr].numberOfDimensions == label1->labelValue.vStruct.numberOfDimensions &&
						vectorLimits[itr].distType == label1->labelValue.vStruct.vectComparisonType)
				{
					normFactor = vectorLimits[itr].maxDistance;
				}
			}
		}

		matchCost = sqrt(matchCost);

		// Normalize using norm factor.
		if (normalized)
		{
			matchCost = matchCost/normFactor;
		}

		break;

	// City block distance
	case DIST_L1:
		for (itr = 0; itr < label1->labelValue.vStruct.numberOfDimensions; ++itr)
		{
			matchCost += fabs(label1->labelValue.vStruct.vectorLabel[itr] -
								label2->labelValue.vStruct.vectorLabel[itr]);
		}

		// Find the true normalization factor for this vector label type.
		if (normalized){
			for (itr = 0; itr < vectorLimitsEntryCount; ++itr) {
				if (!strcmp((char*)vectorLimits[itr].name, label1->labelValue.vStruct.stringLabel) &&
						vectorLimits[itr].numberOfDimensions == label1->labelValue.vStruct.numberOfDimensions &&
						vectorLimits[itr].distType == label1->labelValue.vStruct.vectComparisonType)
				{
					normFactor = vectorLimits[itr].maxDistance;
				}
			}
		}

		// Normalize using norm factor.
		if (normalized)
		{
			matchCost = matchCost/normFactor;
		}
		break;

	default:
		// Errorneous input.
		if (normalized)
			return 1.0;
		else return -1.0;
	}
	return matchCost;
	// If normalized is true, then function is called in LabelMatchFactor() function.
	// Meaning, here we should return default max distance.
	// If not, then the function is called to learn actual max distance.
	// We should set the return value to an invalid distance as a flag.
	if (normalized)
		return 1.0;
}



//---------------------------------------------------------------------------
// NAME:    PrintLabel
//
// INPUTS:  (ULONG index) - index into label list
//          (LabelList *labelList) - list of labels
// 		   (FILE *outputFile) - output file handle
//
// RETURN:  void
//
// PURPOSE: Print label of given index to given file handle.
//---------------------------------------------------------------------------

void PrintLabel(ULONG index, LabelList *labelList, FILE *outputFile)
{
   UCHAR labelType;

   labelType = labelList->labels[index].labelType;
   switch(labelType) 
   {
      case STRING_LABEL:
         fprintf(outputFile, "%s", labelList->labels[index].labelValue.stringLabel);
         break;
      case NUMERIC_LABEL:
         fprintf(outputFile, "%.*g", NUMERIC_OUTPUT_PRECISION,
                 labelList->labels[index].labelValue.numericLabel);
         break;
      case VECTOR_LABEL:
    	  fprintf(outputFile, "%s ", labelList->labels[index].labelValue.vStruct.stringLabel);
    	  fprintf(outputFile, "%d%c%d", (int) labelList->labels[index].labelValue.vStruct.vectComparisonType,
    			  DELIMITER,
    			  labelList->labels[index].labelValue.vStruct.numberOfDimensions);
    	  int dimItr;
    	  for (dimItr = 0; dimItr < labelList->labels[index].labelValue.vStruct.numberOfDimensions; ++dimItr) {
    		  fprintf(outputFile, "%c%lf", DELIMITER, labelList->labels[index].labelValue.vStruct.vectorLabel[dimItr]);
    	  }
    	  break;
      default:
         break;
   }
}


//---------------------------------------------------------------------------
// NAME:    PrintLabelList
//
// INPUTS:  (LabelList *labelList) - list of labels
//
// RETURN:  void
//
// PURPOSE: Print labels in given labelList.
//---------------------------------------------------------------------------

void PrintLabelList(LabelList *labelList)
{
   ULONG i;

   printf("Label list:\n");
   for (i = 0; i < labelList->numLabels; i++) 
   {
      printf("  labels[%lu] = ", i);
      PrintLabel(i, labelList, stdout);
      printf("\n");
   }
}


//---------------------------------------------------------------------------
// NAME: FreeLabelList
//
// INPUTS: (LabelList *labelList)
//
// RETURN: (void)
//
// PURPOSE: Free memory in labelList.
//---------------------------------------------------------------------------

void FreeLabelList(LabelList *labelList)
{
   free(labelList->labels);
   free(labelList);
}


//---------------------------------------------------------------------------
// NAME: WriteLabelToFile
//
// INPUTS: (FILE *outFile) - file to write to
//         (ULONG index) - index of label in label list
//         (LabelList *labelList) - label list
//         (BOOLEAN suppressQuotes) - if TRUE, then delimiting quotes not
//                                    printed
//
// RETURN: (void)
//
// PURPOSE: Write label labelList[index] to given file.  If suppressQuotes
// is TRUE and the label has delimiting end quotes, then do not print them.
//---------------------------------------------------------------------------

void WriteLabelToFile(FILE *outFile, ULONG index, LabelList *labelList,
             BOOLEAN suppressQuotes)
{
   UCHAR labelType;
   char labelStr[TOKEN_LEN];
   int strLength;
   int i;

   labelType = labelList->labels[index].labelType;
   switch(labelType) 
   {
      case STRING_LABEL:
         strcpy(labelStr, labelList->labels[index].labelValue.stringLabel);
         if (suppressQuotes) 
         { // remove delimiting DOUBLEQUOTES if there
            strLength = strlen(labelStr);
            if ((labelStr[0] == DOUBLEQUOTE) &&
                (labelStr[strLength - 1] == DOUBLEQUOTE)) 
            {
               for (i = 0; i < strLength; i++)
                  labelStr[i] = labelStr[i+1];
               labelStr[strLength - 2] = '\0';
            }
         }
         fprintf(outFile, "%s", labelStr);
         break;
      case NUMERIC_LABEL:
         fprintf(outFile, "%.*g", NUMERIC_OUTPUT_PRECISION,
                 labelList->labels[index].labelValue.numericLabel);
         break;
      case VECTOR_LABEL:
    	  fprintf(outFile, "%s ", labelList->labels[index].labelValue.vStruct.stringLabel);
    	  fprintf(outFile, "%d:", (int) labelList->labels[index].labelValue.vStruct.vectComparisonType);
    	  fprintf(outFile, "%d", labelList->labels[index].labelValue.vStruct.numberOfDimensions);
		  int dimItr;
		  for (dimItr = 0; dimItr < labelList->labels[index].labelValue.vStruct.numberOfDimensions; ++dimItr)
			  fprintf(outFile, "%c%lf", DELIMITER, labelList->labels[index].labelValue.vStruct.vectorLabel[dimItr]);
		  break;
      default:
         break;
   }
}
