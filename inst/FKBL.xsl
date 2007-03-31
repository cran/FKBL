<?xml version="1.0" encoding="ISO-8859-1"?>

<html xsl:version="1.0" 
xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns="http://www.w3.org/1999/xhtml">
<link rel="stylesheet" type="text/css" href="FKBL.css"/>
	<body>
		<xsl:if test="KnowledgeBase/Author">
			<div class="titu">Author</div>
			<div class="elem">
        		        <xsl:value-of select="KnowledgeBase/Author"/>
                	</div>
		</xsl:if>
                <xsl:if test="KnowledgeBase/Description">
			<div class="titu">Description</div>
			<div class="elem">
                	<xsl:value-of select="KnowledgeBase/Description"/>
	                </div>
		</xsl:if>
                <xsl:if test="KnowledgeBase/Error">
			<div class="titu">Error in train</div>
			<div class="elem">
        	        <xsl:value-of select="KnowledgeBase/Error"/>%
	                </div>
		</xsl:if>
		<div class="titu">Number of classes</div>
		<div class="elem">
		<xsl:value-of select="KnowledgeBase/numclasses"/>
		</div>
		<div class="titu">Partitions</div>
		<xsl:for-each select="KnowledgeBase/Partition">
		<div class="elem">[<xsl:value-of select="ex"/>]</div>
		</xsl:for-each>

		<div class="titu">Rules</div>		

		<table border="1">
			<tr bgcolor="#9acd32">
			<th>Antecedent</th>
			<th>Consecuent</th>
			</tr>

                <xsl:for-each select="KnowledgeBase/Rule">
                <tr>
		<td align="center"><xsl:value-of select="antecedent"/></td>
		<td align="center"><xsl:value-of select="consecuent"/></td>
		</tr>
                
		</xsl:for-each>

		
		</table>
	</body>
</html>

