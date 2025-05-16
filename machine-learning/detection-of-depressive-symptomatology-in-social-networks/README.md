# Detection of depressive symptomatology in social networks

## Authors:
* **Jhonatan Barcos Gambaro (100548615)**
* **Andrés Díaz Ruano (100472763)**

## Project description
Currently, with regard to mental health, we are witnessing how much of a problem it is for many people. Moreover, it has been deeply aggravated in the aftermath of the COVID-19 pandemic. According to the WHO, by 2023 almost one in two people in the European Union (46%) had experienced emotional or psychosocial problems in the last 12 months.

These mental health problems also have an economic impact, costing 4% of the GDP of EU countries. Furthermore, the ‘Health at a Glance’ report carried out in 2022 showed that almost one in two young people report having unmet mental health needs. 

The depressive symptomatology of these young people in several EU countries has more than doubled since the pandemic. These data clearly show that there is a huge unmet need with regard to mental health. 

Through this project, we aim to detect depressive symptomatology in social media posts through a Dataset of posts on Reddit providing a reliable method for the detection of these individuals and their treatment.

##  Dataset Description
This dataset is designed for a **binary classification task** aimed at detecting signs of depression in Reddit posts. Each post is labeled as either:

- **1 = Depressed** (originating from mental health-related subreddits)
- **0 = Non-depressed** (from general-interest subreddits)

The posts were collected from six subreddits, grouped by mental health relevance:

- **Depressive sources:**
  - `r/Depression`
  - `r/SuicideWatch`

- **Non-depressive sources:**
  - `r/Teenagers`
  - `r/DeepThoughts`
  - `r/Happy`

Each entry in the dataset contains the following fields:

- `subreddit`: the subreddit where the post was published  
- `title`: the post’s title (often a summary or strong emotional statement)  
- `body`: the main content of the post, where most linguistic cues are found  
- `upvotes`: number of upvotes received (can reflect engagement or sentiment resonance)  
- `created_utc`: UTC timestamp of when the post was created  
- `num_comments`: number of comments received (a proxy for interaction or support)  
- `label`: target variable (0 = non-depressed, 1 = depressed)

Our goal is to explore how different representations capture the emotional and semantic structure of the posts, and assess their usefulness in downstream tasks such as classification or visualization.

# 1. Natural Language Processing, Topic Modeling and Document Vectorization
## 1.1. Preprocessing Pipeline
In this section, we will define the preprocessing carried out on our dataset to adapt it in the best possible way to our project. As a previous step to make the corresponding code, we have made a detailed analysis of the language of our dataset, which we have to take into account that it comes from social network posts, so we find an informal language, with spelling mistakes and/or abbreviations due to the inherent language of social networks. This initial analysis has been key to perform an optimal preprocessing pipeline for our practice.

Below, we detail the preprocessing performed with the aim of cleaning and normalizing the text of our dataset to increase the quality of its representation and subsequent modeling:

First, we have made the concatenation of the title and body of the messages in a single text string for each of the posts. Then, we have casted the text to lowercase, thus reducing the sparsity of the vocabulary. On the other hand, one of the difficulties we have encountered due to the nature of the social networking language is the presence of HTML tags, URLs and user mentions, so we have removed them using regex. Once this initial preprocessing was done, we used the en_core_web_md model to tokenize the vocabulary.

Then, the lemmatization of each token was performed, followed by a final filtering based on the elimination of the following elements:
* Punctuation marks
* Special characters
* Stopwords (coming from SpaCy modified to adapt it to our practice)
* Tokens smaller than 3 characters.
  
Once this preprocessing was done, each document was represented as a clean list of lemmatized tokens prepared for vectorization, which is detailed below.

## 1.2. Text Vectorization
In the following section we will describe all the strategies we have chosen and implemented in our project with the aim of representing texts through numerical vectors for their subsequent use in topic analysis and classification tasks.


### 1.2.1. TF-IDF representation
First of all, we have used a TF-IDF (Term Frequency-Inverse Document Frequency) representation, a technique based on the weighting of terms according to their frequency in the occurrence of a document versus their frequency within the corpus. This feature is the key reason why we have decided to choose this representation over BoW, since with TF-IDF we achieve a key semantic discrimination for our project, since if we had used BoW, very common words in social networks would pose a problem for the subsequent binary classification.

To carry out its implementation we have used TfidfVectorizer from scikit-learn, using as input the preprocessed texts detailed above. Likewise, we have considered unigrams and bigrams, limiting to 5,000 features to avoid model confusion and maximize accuracy. We also normalized the vectors to provide stability in the new data for later use as input to classification models.

Finally, we print a visualization with Word Cloud, which is attached below. We can observe a word cloud where those terms that have a higher weight in our representation appear.

<img width="399" alt="Captura de pantalla 2025-05-05 191116" src="https://github.com/user-attachments/assets/5b710e9d-8fad-49fe-a7b7-1236d89f6f0c" />

We can observe how words like “feel”, “think”, “hug”, “life”, ‘want’ and “know”.  This is coherent because they reflect an introspective and emotional tone, which have a great weight at a psychological level.

### 1.2.2. Word2vec/Glove based representation
Next, we will perform a scan with pre-trained and locally trained embeddings to capture the semantic relationships between words in our corpus based on Reddit posts. For this purpose, we have chosen the 100-dimensional Word2Vec and GloVe6B representations.

Regarding the Word2Vec model, we have trained it on our corpus using gensim.models.Word2Vec with the following parameters:
vector_size=100
window=5
min_count=5 
workers=4
sg=1 
Thus, once we have trained the model, each document has been represented as the average of the vectors of its words, which is equivalent to the average of embeddings.

Concerning the GloVe model, we used pre-trained embeddings, specifically glove.6B.100d.txt, which we downloaded from the official GloVe website. As with Word2Vec, this model computes the vector for each document as the average of the vector of its words.

In the following, we will explain in a theoretical-mathematical way how these models carry out the conversion from words to vectors in each of the documents. First of all, the input of these models is a tokenized text d = [t1, t2, t3, ..., tn] (detailed in previous points), while the embeddings model E(ti) = R^100. Thus we can define the representation of a document as:
doc = 1/n SUM_i=1_n(E(ti))

Through this representation technique we preserve the semantic meaning of the texts and we are able to generate dense 100-dimensional representations.  

To conclude this section, we have performed a 2 dimensions PCA analysis to check which is the best model for vector adaptation of the informal language inherent in our Reddit corpus. The different visualizations are attached below. 

#### 2D PCA Visualization of Word2Vec Document Vectors:
<img width="553" alt="word" src="https://github.com/user-attachments/assets/e813bf7c-937e-49ea-b5b3-74c7a9ef91eb" />

#### 2D PCA Visualization of Glove Document Vectors:
<img width="548" alt="glove" src="https://github.com/user-attachments/assets/16ae264d-9ee4-4613-8ce2-c7e9ec728a1e" />

Through an in-depth analysis of the results, we observe that the Word2Vec model explains 17.35% of the variance of our vectorized data in the first principal component (PC1) and 8.38% in the second one (PC2). In contrast,  the GloVe model accounts for 14.77% with PC1 and 8.01% with PC2. Thus, the results suggest that the Word2Vec embedding captures a slightly higher amount of variance in the data, potentially offering a better separation between the document classes in a reduced 2-dimensional space. The better performance of Word2Vec may be attributed to its ability to capture local semantic context more effectively than GloVe, which is particularly relevant in task involving emotional expressions, such as depression detection in social media texts.

### 1.2.3. Extraction of themes and vector representation of the documents using the LDA algorithm
To conclude this section we will describe the topic extraction and vector representation of the documents through the LDA algorithm, implemented with gensim. The main goal of this method is to model latent topics and extract common discourse patterns among the main topics of our corpus. To carry out such implementation we have limited the tokens according to their frequency, eliminating tokens with a very high or low relative frequency (in case they appear in less than 5% or more than 80% of documents). This ensures that all tokens provide relevant information to the model while improving its performance. A bag of words was then created through doc2bow from the dictionary.

In order to maximize the efficiency of this method we used an iterative technique to select the optimal number of topics for the LDA algorithm according to our project. For this purpose, we have trained LDA models with the following k parameters:

* start = 5
* limit = 30
* step = 5
  
We have then evaluated each of the models using semantic coherence as a criterion through gensim.models.CoherenceModel and we have concluded that the best value for our algorithm is k=10 as it has obtained the highest coherence. Thus, each document is transformed into a 10-dimensional vector where each component represents the probability of belonging to a topic. Finally, we store the best model for later use in classification models.


Below is an image with the list of the most relevant words of each topic as well as the general interpretation of each topic for the correct understanding of the classification.

![topics_word_table_colored_header_big](https://github.com/user-attachments/assets/049ab3a4-77fb-4e18-8ba8-db070a2db74d)


# 2. Machine Learning. Classification using feature extraction or selection techniques
The goal for this task is to build a binary classification model capable of distinguishing between reddit users that show depression signs and those who do not, based on the content of their posts. The classification is based on the label variable, where:
0 corresponds to users from non-depressive subreddits (`r/Teenagers`, `r/DeepThoughts`, `r/Happy`), representing the control group.
1 corresponds to the users belonging to depressive subreddits (`r/Depression`, `r/SuicideWatch`).

The primary objective is to explore how different text vectorizations, feature representations and selection techniques affect the classification performance. The summary of dimensions of each vectorization technique we tested:
TF-IDF: it is sparse and high dimensional. We limited the vocabulary to the 5000 most relevant tokens.
GloVe: dense 100-dimensional vector per document.
Word2Vec:  dense 100-dimensional vector per document.
LDA: dense 10-dimensional vector per document.

## 2.1. Feature extraction and selection techniques
To improve both the interpretability and performance of our classifiers we applied a variety of dimensional reduction techniques, covering both feature extraction and selection approaches. These techniques were systematically applied to all four types of document representations we explored in Task1: TF-IDF, Word2Vec, GloVe and LDA.

### 2.1.1. Feature extraction 

#### 2.1.1.1. Principal Component Analysis (PCA)
To reduce dimensionality while preserving as much variance as possible we applied PCA to each text representation technique. PCA is an unsupervised technique that transforms the original features into a new set of orthogonal components ordered by the amount of variance they explain.
Implementation details: 
Sparse matrix handling: if the input is in sparse format (as in TF-IDF), it is first converted into a dense array.
Standardization: we standardize the input features to ensure all variables contribute equally to the PCA and avoid the sensitive scaling of this algorithm.
We set the maximum number of components to 10 (depending on the dimensionality), which means PCA will extract the 10 most significant components (the ones that explain the higher percentage of the variance).

#### 2.1.1.2. Partial Least Squares (PLS) Regression
PLS is a supervised feature extraction technique that projects both the predictors and the target variable into a new space by maximizing the covariance between them. It is especially useful for high-dimensional and collinear features.
Implementation details:
As in PCA, input vectors were converted to dense arrays if necessary.
Standardization: both input and target are standardized to ensure stability.
Target reshaping: The target variable is shaped into a 2-dimensional array
We extract the 10 latent variables that better capture the relationship between features and target.

The final result X_pls is a new representation of each document in a 10-dimensional space optimized to explain variation relevant to the classification task..	

### 2.1.2. Feature selection
In addition to feature extraction we applied several feature selection methods to identify the most informative features for each vectorization. These methods are grouped into three categories: filtering, wrapper and embedded.

#### 2.1.2.1. Filtering - SelectKbest
We used SelectKBest with the mutual information criterion to rank features by their dependency with the target variable. This method is able to capture both linear and nonlinear relationships.
We select the top 100 features with the higher MI score (higher dependency).
It works well with high-dimensional inputs, such as TF-IDF.
The benefits of this approach are its simplicity, speed and that it is model-agnostic.

#### 2.1.2.2. Wrapper – Recursive Feature Elimination (RFE)
RFE is a greedy optimization technique that recursively removes the least important features based on the weights of a base model.
We set logistic regression (linear) as the base model with a maximum of 500 iterations. 
It keeps the top 100 features after iterative elimination.
It improves relevance.

#### 2.1.2.3. Embedded – L1-Regularized Logistic Regression and Random Forest
Embedded methods perform feature selection within the model training itself. We have used two different approaches:

L1-Regularized Logistic Regression (LASSO): It introduces a penalty term that forces the model to shrink some features' weight to zero. In this way it eliminates less relevant features while retaining those which are more useful for the prediction. After fitting the model we select the top 100 features with higher weights. This method is especially effective when dealing with high-dimensional data such as TF-IDF, improving generalization.
Random Forest: On the other hand, we have used RF, an ensemble method based on decision trees that allows us to measure how important each feature is. It does this by checking how much each feature helps to split the data correctly across all the trees in the model. We ranked the features using the feature_importances_  attribute and selected the top 100 with the highest scores. This method doesn’t make strong assumptions about the data, can deal with complex (non-linear) patterns, and works well even when there is noise or useless features in the dataset.

### 2.1.3. Generation of reduced feature sets
For each type of vectorization (TF-IDF, Word2Vec, GloVe, LDA), we applied all the feature extraction and selection methods, using the same settings: up to 10 components for PCA and PLS, and up to 100 features for SelectKBest, RFE, and L1-based selection. We stored the results in a dictionary to keep everything organized and printed the shapes of each output to make sure the transformations worked correctly. As a result, we obtained 20 reduced feature sets in total (4 vectorizations × 5 methods), which were then used to train and evaluate our classification models.

## 2.2. Classification pipeline and evaluation
This section covers how the data was split, which models were used and how we measured their performance. Each model was trained using the different vectorizations and feature sets obtained  in the previous section to compare which combinations gave the best results.

### 2.2.1. Data splitting and validation strategy
To evaluate the performance of our models we split the dataset into 80% for training and 20% for testing. We used stratified sampling to make sure that both classes (depressed and non-depressed) were represented in similar proportions in both sets.
During training, we applied 5-fold cross-validation to select the best hyperparameters and avoid overfitting. This method divides the training data into five parts: four are used to train the model, and one is used to validate it. This process is repeated five times so that every part is used for validation once. It helps us get a more reliable estimate of how well the model generalizes to new data.

### 2.2.2. Models used
We tested different classification models to see which ones worked best with our data. The idea was to combine simple and more complex models to understand how each one performs with the different types of features we created.

#### 2.2.2.1. Logistic Regression
We used Logistic Regression as a baseline model because it is simple, fast, and often performs well in text classification tasks. It is a linear classifier that models the probability that a sample belongs to the positive class using the sigmoid function applied to a weighted sum of the input features:
P(y=1∣x)=1/(1+e^(-(w^T x+b)))
The model is trained by minimizing the logistic loss (also called cross-entropy loss), which penalizes incorrect predictions. We also apply L2 regularization to the weights to prevent overfitting, especially in high-dimensional cases.
We implemented the model through a pipeline that included feature scaling (without centering to support sparse matrices) followed by a LogisticRegression estimator using the liblinear solver. We tuned the regularization strength using a grid search over several values of C ([0.01, 0.1, 1, 10, 100]) for each combination of vectorization and dimensionality reduction methods.

#### 2.2.2.2. Random Forest
Random Forest is a machine learning model based on decision trees. Instead of using just one tree, it builds many trees using random parts of the data and then combines their predictions. This makes the model more stable and helps reduce overfitting. It's also good at working with noisy or irrelevant features, and it can capture non-linear patterns in the data.
Each tree decides how to split the data by checking which features reduce the classification error the most. At the end, the final prediction is made by majority vote across all trees. Another useful property is that Random Forest gives us feature importance scores, showing which variables were most helpful during training.

In our case, we trained one model for each feature set, without applying any scaling (since Random Forest doesn’t need it). We used grid search to test different hyperparameter combinations:
n_estimations: number of trees (100 and 200)
max_depth: tree depth (None, 10, 20)
min_sample_split: minimum samples to split a node (2,5)
Each model was trained using 5-fold cross-validation and later evaluated on a separate 20% test set for every vectorization and dimensionality reduction method.

#### 2.2.2.3. Support Vector Machine (SVM)
SVM is a linear classifier that tries to find the best hyperplane that separates the two classes by maximizing the margin between them. This margin is the distance between the hyperplane and the closest points from each class. A larger margin usually leads to better generalization of new data. SVM works well in high-dimensional spaces, which makes it suitable for text classification tasks.
In our implementation, we used a linear kernel and added MinMax scaling to the features to improve convergence during training. Since SVM is sensitive to the scale of the input, scaling was essential, especially after applying dimensionality reduction.
For feature sets obtained through selection methods, we noticed they were still too high-dimensional or noisy, so we applied PCA to reduce them to a maximum of 10 components before training the model.
We tuned the regularization parameter C using grid search with the values [0.01, 0.1, 1, 10], and trained each model using 5-fold stratified cross-validation. Each configuration was then evaluated on a 20% test set.

### 2.2.3. Evaluation metrics and results
To evaluate the performance of our classification models, we used a set of standard metrics that give insight into different aspects of the predictions:
Accuracy: the proportion of correctly predicted samples.
Precision: how many of the predicted positives were actually corre
Recall: how many of the actual positives were correctly identified.
F1-score: the harmonic mean of precision and recall, especially useful in imbalanced datasets.
ROC-AUC: measures the ability of the model to distinguish between classes across all thresholds.
Confusion Matrix: a breakdown of true vs. predicted labels for both classes.

#### Logistic Regression
Logistic Regression achieved excellent results, especially when combined with the TF-IDF vectorization and strong feature engineering techniques. The best configuration, TF-IDF + PLS, reached an F1-score of 0.98 and a ROC AUC of 0.99, showing exceptional balance between precision and recall. Feature selection methods like KBest, RFE, and Embedded also performed consistently well, particularly with Word2Vec, which benefited from dense representations.
Although GloVe achieved moderate performance (F1-scores ~0.87), LDA remained the weakest representation, with F1-scores around 0.77–0.79. Most optimal models selected C = 10.0 or 0.1, indicating that moderate regularization leads to better generalization.

#### Random Forest
Random Forest classifiers also performed strongly across all feature sets. Word2Vec + Embedded selection worked well, with an F1-score of 0.86 and ROC AUC of 0.91. Dense embeddings like Word2Vec and GloVe showed great compatibility with tree-based models, especially when feature selection was applied. TF-IDF remained a reliable option, with PLS and PCA achieving F1-scores >0.89.
LDA showed slight disimprovement over its performance with Logistic Regression, with top scores around 0.71, showing that Random Forest can better handle topic-based representations. Most top configurations used 100–200 trees and max_depth between 10 and 20, confirming that moderately deep trees generalize well in this task.

#### Support Vector Machine (SVM)
Linear SVM models performed exceptionally well after dimensionality reduction. The best result came from TF-IDF + PLS, reaching an F1-score of 0.95, ROC AUC of 0.99, and very high precision (0.99) and recall (0.99). PCA also improved performance, particularly when applied after feature selection methods like KBest and RFE.
GloVe and Word2Vec achieved solid F1-scores (~0.85–0.88) and strong ROC AUC values (~0.91–0.93), confirming good calibration even when linear SVMs are used. LDA again lagged behind, though it slightly underperformed its results from the other models (best F1 ≈ 0.66). All best models chose C = 10.0, suggesting that low regularization works best when data is well-normalized.

### Comparative Analysis
Across all models, the TF-IDF + PLS configuration consistently emerged as the top performer, especially for Logistic Regression and SVM, with F1-scores near 0.98–0.99. This is likely due to TF-IDF’s ability to capture fine-grained lexical patterns in the posts, combined with PLS’s effectiveness in projecting features into a space that maximally correlates with the target labels. Since Reddit posts related to depression often include emotionally charged vocabulary, TF-IDF retains this discriminative detail better than other vectorizations.

Word2Vec with Embedded selection, on the other hand, produced the best results for Random Forest. This makes sense given that Random Forest handles dense, non-linear feature spaces well, and Word2Vec captures semantic relationships between words that may not be reflected in simple term frequency. Feature selection here likely removed noise and retained the most meaningful semantic axes.

GloVe also performed reasonably well across models but slightly under TF-IDF and Word2Vec. While it captures global co-occurrence information, its fixed nature (pre-trained) might miss Reddit-specific expressions or informal patterns relevant to the task.
Finally, LDA was consistently the weakest vectorization, with lower F1-scores across all models. This is expected in binary classification tasks like this one, where topic distributions are often too coarse to separate nuanced emotional states. However, even LDA benefited from dimensionality reduction and selection, suggesting that while topic-level features are less informative alone, they still carry some class-discriminative signal when combined with the right model.


# 3. Dashboard for the Detection of Depressive Symptomatology in Social Networks
To finalize the project, an interactive dashboard has been implemented where the user can check the final results of the main project notebook and make an exhaustive comparison of the results obtained according to the combination of the different classification and vectorization models implemented, which have been detailed in the previous points.

In order to facilitate the use of this tool, all the modules that have been implemented dynamically are detailed below:

## 3.1. Section A: Analysis and exploration at the topic level (Modules 1-4)
### Module 1: Distribution of documents by topic 
In this module we can observe a bar chart representing the number of posts in our Reddit corpus that fall into each topic according to the results of our best LDA configuration. This way we can see which are the most relevant topics in our dataset.

### Module 2: Key words for the selected topic
Next, after the selection of a certain dominant topic, the most relevant words of that topic are displayed to favor the semantic understanding of the topic and thus favor the clarity of the subsequent analysis of that topic.

### Module 3: Distribution of tags for the selected topic
Next, we visualize a comparison between the distribution of tags (control vs. depression) for the selected topic. This helps us to determine which topics have a higher correlation with depressive symptomatology, which together with the previous module will constitute an essential part of the project analysis.

### Module 4: 2D Document Projection (PCA)
To conclude this section, we have made a scatter plot using principal component analysis in 2D space. Thus, we allow the user to visualize the separation between the 2 different classes using embeddings.

## 3.2. Section B: Exhaustive comparison of different models (Module 5)
### Module 5: Exhaustive Comparison: Model, Vectorizer & Feature Selection
In this section we will perform an exhaustive and interactive analysis where the user will be able to select the different parameters to visualize the results of a given combination of parameters for each of the models and even compare them with other combinations of parameters. Thus the user will be able to filter the results by:
* Evaluation Metric
* Filter by Model
* Filter by Vectorizer
* Filter by Feature Selection

Once this selection has been made, two different visualizations of the comparison of the results will be printed. First, a dynamic bar chart, where we can easily and quickly visually identify the best parameter configuration. Finally, an interactive table where we can see in greater mathematical detail the results for the selected combinations.

# Acknowledgment of authorship
We, Jhonatan Barcos Gambaro (100548615) and Andrés Díaz Ruano (100472763), declare that the work done in this project has been designed, implemented, evaluated and described in this report by us. This includes each of the following sections:

* The preprocessing pipeline for Reddit posts

* The document vectorization strategies: TF-IDF, Word2Vec, GloVe, and LDA

* The training, evaluation, and comparison of machine learning models using various feature selection techniques

* The development of the interactive dashboard using Dash and Plotly

To carry out the practice we used as a main reference the notebooks provided in the course Machine Learning Applications, whose authors are Vanessa Gómez Verdejo, Jerónimo Arenas-García, Lorena Calvo-Bartolomé, and Jesús Cid-Suero. We also referenced materials from the Natural Language Processing course, developed by Pablo Martínez Olmos and Ángel Navia Vázquez.

In addition, we used generative AI tools such as ChatGPT from OpenAI and Copilot in combination with Prompt Engineering techniques to maximize the usefulness and correctness of these tools. In the following section we propose a statement of generative AI usage on this project where we have reflected on the use of these new tools.

## Declaration of use of generative Artificial Intelligence

### For which aspects of the practice we have used AI?
* Definition and understanding of the objectives of our project: First of all, we have used generative AI to guarantee a correct and complete understanding of the objectives of the practice at a technical and mathematical level. Likewise, we have been able to establish the statement through practical examples to be able to develop the practice with total guarantees at the level of understanding.

* Resolving doubts about the problems that arose during the development of the practice: As we were solving the proposed statement, different problems arose at code level as execution errors, which we easily solved through VSCode debugging with the help of generative AI to detect where in our code was the error in order to solve it.
  
* Complex code writing guided by the provided notebooks and prompt engineering techniques to adapt our base code with new modalities in order to simplify our initial implementation and improve the results based on the different evaluation methods used.
Code review and validation of our model: Once our code was finalized, we performed an exhaustive analysis of it to verify that it was correct.

### To what extent has it facilitated the realization of the practice?
In general, access to these new tools in a responsible and coherent way has been a great advantage when carrying out the practice, especially in terms of time, since it has facilitated different aspects such as:

* Quick understanding of complex concepts, for which, in the past, it would take us much more time to find the indicated information on the internet, interpret it and adapt it to our needs.
  
* Resolution of errors, for which, as in the previous point, in the past we could take a long time to detect and solve correctly.
Obtaining explanations about python library methods that we do not know in depth in a much faster and more efficient way than consulting the library guide.

* Verification of the content of the memory to verify that we did not leave anything relevant for the total understanding of our work developed in this practice.

### How did we verify and adapt the information obtained?
As mentioned in the previous section, we consider the use of these new tools to be a great advantage over the past, as long as they are used responsibly and conscientiously. Therefore, we have used a cross-validation method to ensure that the information provided by the generative AI was correct and optimal. For this purpose, the following methodology was followed:

* Checking on the validity of the answers through the Internet and resources provided in the referenced notebooks.
  
* Contrasting the theoretical explanations with the Internet and referenced notebooks, especially in the mathematical part since the generative AIs are not perfected in this area.

* Use of AI as a support tool and not as a substitute for critical thinking to solve the different problems posed.




