import plotly.graph_objects as go
import re

GLOBAL_ASM_REGEX = r'\#pragma\sGLOBAL_ASM[(]".*(?=\/)\/([^.]+).s"[)]'

class ScoreTreemap:
    def __init__(self, map_file):
        self.map_file = map_file

    def generateTreemapData(self, score_files, code_size):
        """Prepare data for treemap visualization."""
        labels = ["Decomp"]
        parents = [None]
        values = [0]
        colours = [None]
        legends = [None]

        for scoreFile in score_files:
            parentName = scoreFile.path.replace('./src/', '')

            for func in scoreFile.functions:
                color = '#92ac68'
                legend = 'matched'
                if func.isDocumented:
                    color = 'green'
                    legend = 'documented'

                labels.append(func.functionName)
                parents.append(parentName)
                values.append(func.size)
                colours.append(color)
                legends.append(legend)

            matches = re.finditer(GLOBAL_ASM_REGEX, scoreFile.text, re.MULTILINE)
            for match in matches:
                funcName = match.groups()[0]
                if funcName in self.map_file.functionSizes:
                    size = self.map_file.functionSizes[funcName]

                    color = "grey"
                    legend = "N/A"
                    if funcName in scoreFile.nonMatchings:
                        color = 'orange'
                        legend = "non matching"
                    elif funcName in scoreFile.nonEquivalents:
                        color = 'red'
                        legend = "non equivalent"

                    labels.append(funcName)
                    parents.append(parentName)
                    values.append(size)
                    colours.append(color)
                    legends.append(legend)

            labels.append(parentName)
            parents.append("Decomp")
            values.append(0)
            colours.append(None)
            legends.append(None)

        return labels, parents, values, colours, legends

    def generateTreemap(self, score_files, output_path, selected_version, code_size):
        print(f"Generating progress treemap, outputting file to {output_path}")

        # Prepare data
        labels, parents, values, colours, legends = self.generateTreemapData(
            score_files, code_size
        )

        # Calculate statistics for each parent file
        file_stats = {}
        for scoreFile in score_files:
            parentName = scoreFile.path.replace('./src/', '')
            file_stats[parentName] = {
                'matched': 0,  # Total matched functions (includes documented)
                'documented': 0,  # Only documented functions
                'non matching': 0,
                'non equivalent': 0,
                'N/A': 0
            }

            # Count all matched functions (both documented and non-documented)
            matched_count = 0
            for func in scoreFile.functions:
                matched_count += 1  # All functions in scoreFile.functions are matched
                if func.isDocumented:
                    file_stats[parentName]['documented'] += 1

            file_stats[parentName]['matched'] = matched_count

            # Count non-matched functions
            matches = re.finditer(GLOBAL_ASM_REGEX, scoreFile.text, re.MULTILINE)
            for match in matches:
                funcName = match.groups()[0]
                if funcName in self.map_file.functionSizes:
                    if funcName in scoreFile.nonMatchings:
                        file_stats[parentName]['non matching'] += 1
                    elif funcName in scoreFile.nonEquivalents:
                        file_stats[parentName]['non equivalent'] += 1
                    else:
                        file_stats[parentName]['N/A'] += 1

        # Create custom hover text
        hover_texts = []
        for i, label in enumerate(labels):
            parent = parents[i]
            value = values[i]

            if label == "Decomp":
                # Decomp root should have no label
                hover_texts.append("")
            elif value == 0:
                # Parent nodes (file names) - show statistics
                if label in file_stats:
                    stats = file_stats[label]
                    hover_text = f"<b>{label}</b><br>"

                    # Add each statistic only if it's > 0
                    stat_lines = []
                    if stats['matched'] > 0:
                        # Show total matched functions (includes documented)
                        stat_lines.append(f"Decompiled functions: {stats['matched']}")
                    if stats['documented'] > 0:
                        # Documented is a subset of matched
                        stat_lines.append(f"Documented functions: {stats['documented']}")
                    if stats['non matching'] > 0:
                        stat_lines.append(f"Non matching functions: {stats['non matching']}")
                    if stats['non equivalent'] > 0:
                        stat_lines.append(f"Non equivalent functions: {stats['non equivalent']}")
                    #if stats['N/A'] > 0:
                    #    stat_lines.append(f"Unknown status: {stats['N/A']}")

                    hover_text += "<br>".join(stat_lines)
                    hover_texts.append(hover_text)
                else:
                    hover_texts.append(f"<b>{label}</b>")
            else:
                # Function nodes - show size information
                percent = value / code_size * 100
                hover_texts.append(f"<b>{label}</b><br>{value} bytes ({percent:.2f}%)")

        # Filter out 0-byte values for the treemap (but keep them for structure)
        display_values = [v if v > 0 else 1 for v in values]  # Use 1 as minimal value for parent nodes

        # Create the treemap figure
        fig = go.Figure(go.Treemap(
            labels=labels,
            parents=parents,
            values=display_values,  # Use filtered values
            text=hover_texts,
            hovertemplate='%{text}<extra></extra>',
            marker=dict(colors=colours),
            root_color="lightgrey",
            textinfo="none"  # Hide default text labels
        ))

        # Add custom legend using annotations
        legend_items = [
            ("green", "documented"),
            ("#92ac68", "matched"),
            ("orange", "non matching"),
            ("red", "non equivalent"),
            ("grey", "N/A")
        ]

        annotations = []
        for i, (color, label) in enumerate(legend_items):
            annotations.append(dict(
                x=1.1,
                y=1 - (i * 0.05),
                xref="paper",
                yref="paper",
                showarrow=False,
                text=f"<span style='color:{color}'>■</span> {label}",
                font=dict(size=12)
            ))

        fig.update_layout(
            margin=dict(t=50, l=25, r=150, b=25),  # Extra right margin for legend
            title=f"Decomp Progress [{selected_version}]",
            annotations=annotations
        )

        # Save to HTML file
        fig.write_html(output_path)
        print(f"Treemap saved to {output_path}")
